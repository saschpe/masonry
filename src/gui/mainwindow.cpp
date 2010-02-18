/*
    Copyright (c) 2009 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009 Sascha Peilicke <sasch.pe@gmx.de>

    This application is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This application is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this application; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "mainwindow.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/configdialog.h"
#include "graph/graphscene.h"
#include "graph/graphview.h"
#include "graph/items/directededgeitem.h"
#include "graph/items/nodeitem.h"
#include "widgets/editdockwidget.h"
#include "widgets/nodedetaildockwidget.h"
#include "widgets/outputdockwidget.h"

#include <QCloseEvent>
#include <QDir>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>
#include <QTextStream>
#include <QTimer>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_scene(new GraphScene), m_view(new GraphView(m_scene))
    , m_process(new QProcess(this)), m_backendInputFile(NULL)
    , m_graphChangesUnsaved(false)
{
    setupUi(this);
    setCentralWidget(m_view);

    setupActions();
    setupDockWidgets();
    setupToolbars();
    readSettings();

    connect(m_process, SIGNAL(started()), this, SLOT(disableWidgets()));
    connect(m_process, SIGNAL(finished(int)), this, SLOT(processFinished()));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError()));
    connect(m_scene, SIGNAL(graphChanged()), this, SLOT(graphChanged()));
    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(graphSelectionChanged()));
    connect(m_scene, SIGNAL(inputNodeChanged()), this, SLOT(graphInputOutputNodesChanged()));
    connect(m_scene, SIGNAL(outputNodeChanged()), this, SLOT(graphInputOutputNodesChanged()));
    connect(m_scene, SIGNAL(sceneRectChanged(const QRectF)), this, SLOT(uncheckZoomToFitAction()));
    connect(m_view, SIGNAL(zoomChanged()), this, SLOT(uncheckZoomToFitAction()));

    removeColumnAction->setEnabled(m_scene->columnCount() > 0);
    removeRowAction->setEnabled(m_scene->rowCount() > 0);

    statusBar()->showMessage(tr("Ready"));
    QTimer::singleShot(100, this, SLOT(checkForFirstStart()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (checkForUnsavedChanges() != QMessageBox::Cancel) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_newAction_triggered()
{
    if (checkForUnsavedChanges() != QMessageBox::Cancel) {
        m_scene->init();
        m_lastFileName = "";
        m_graphChangesUnsaved = false;
        m_process->close(); // If there was a computation running
        enableWidgets();
    }
}

int MainWindow::checkForUnsavedChanges()
{
    int ret = -1;
    if (m_graphChangesUnsaved) {
        QMessageBox box;
        box.setWindowTitle(tr("Masonry"));
        box.setText(tr("This graph has been modfied."));
        box.setInformativeText(tr("Do you want to save your changes?"));
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        ret = box.exec();
        switch (ret) {
            case QMessageBox::Save:
                m_graphChangesUnsaved = false;
                break;
            case QMessageBox::Discard:
                //m_graphChangesUnsaved = false;
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
    return ret;
}

void MainWindow::on_loadAction_triggered()
{
    if (checkForUnsavedChanges() != QMessageBox::Cancel) {
        const QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Masonry Graph File"),
            QDir::currentPath() + QDir::separator() + "data" + QDir::separator() + "graphs",
            tr("Masonry Graph Files (*.masonry)"));
        m_scene->loadFrom(fileName);
        m_lastFileName = fileName;
        m_graphChangesUnsaved = false;
        m_process->close(); // If there was a computation running

        enableWidgets();
        statusBar()->showMessage(tr("File '%1' loaded").arg(m_lastFileName), 3000);
    }
}

void MainWindow::on_saveAction_triggered()
{
    if (m_lastFileName.isEmpty()) {
        on_saveAsAction_triggered();
    } else {
        m_scene->saveTo(m_lastFileName);
        m_graphChangesUnsaved = false;
        statusBar()->showMessage(tr("File '%1' saved").arg(m_lastFileName), 3000);
    }
}

void MainWindow::on_saveAsAction_triggered()
{
    const QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Masonry Graph File"),
        QDir::currentPath() + QDir::separator() + "data" + QDir::separator() + "graphs" +
            QDir::separator() + "untitled",
        tr("Masonry Graph Files (*.masonry)"));
    m_scene->saveTo(fileName);
    m_graphChangesUnsaved = false;
    m_lastFileName = fileName;
    statusBar()->showMessage(tr("File '%1' saved").arg(m_lastFileName), 3000);
}

void MainWindow::on_computeAction_triggered()
{
    delete m_backendInputFile;                              // Remove old temporary netfile and
    m_backendInputFile = new QTemporaryFile;                // create a new one

    if (m_backendInputFile->open()) {                       // Open backend input netfile
        QTextStream stream(m_backendInputFile);

        m_outputDockWidget->clear();                        // Reset output widget contents
        m_outputDockWidget->append(tr("Input:\n\n"));

        int counter = 1;                                    // Generate backend input netfile contents
        foreach (const DirectedEdgeItem *edge, m_scene->edges()) {
            const QString from = edge->start()->name();     // Parse all edges in the scene and
            const QString to = edge->end()->name();         // Generate netfile contents from those
            const QString line = QString::number(counter++) + ' ' + from + ' ' + to + ' ' + edge->name();
            m_outputDockWidget->append("    " + line + '\n');
            stream << line << endl;
        }
        m_backendInputFile->close();                        // Save and close the input netfile
        const QString inputNodeName = m_scene->inputNode()->name();
        const QString outputNodeName = m_scene->outputNode()->name();

        // Create call to 'mason' script with supplied arguments
        QString mscript = QString("mason('%1',%2,%3)")      // Create the call to the 'mason' Matlab
            .arg(m_backendInputFile->fileName())            // function
            .arg(inputNodeName.toInt()).arg(outputNodeName.toInt());

        QString backend;                                    // Check the settings which backend was
        QSettings settings;                                 // configured and generate the commmand
        settings.beginGroup("backend");                     // line to execute
        if (settings.value("current", "octave").toString() == "octave") {
            settings.beginGroup("octave");
            backend = settings.value("executable").toString() + ' ' + settings.value("parameters").toString();
            settings.endGroup();
        } else {
            settings.beginGroup("matlab");
            backend = settings.value("executable").toString() + ' ' + settings.value("parameters").toString();
            settings.endGroup();
        }
        settings.endGroup();

        // Start the backend process with our Matlab script and the generated command line
        m_outputDockWidget->append(tr("\nCommand Line:\n\n    ") + backend.arg(mscript) + "\n");
        m_outputDockWidget->append(tr("\nResults:\n\n"));
        m_process->start(backend.arg(mscript));

        statusBar()->showMessage(tr("Compute response from input node '%1' to output node '%2'...").arg(inputNodeName).arg(outputNodeName));
    } else {
        statusBar()->showMessage(tr("Unable to create temporary file!"), 3000);
    }
}

void MainWindow::on_configureAction_triggered()
{
    ConfigDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        readSettings();
    }
    statusBar()->showMessage(tr("Settings saved"), 2000);
}

void MainWindow::on_helpAction_triggered()
{
    // TODO: Show help
}

void MainWindow::on_aboutAction_triggered()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_aboutQtAction_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::graphChanged()
{
    removeColumnAction->setEnabled(m_scene->columnCount() > 0);
    removeRowAction->setEnabled(m_scene->rowCount() > 0);
    m_graphChangesUnsaved = true;
}

void MainWindow::graphSelectionChanged()
{
    if (m_scene->selectedNode() || m_scene->selectedEdge()) {
        deleteSelectedItemAction->setEnabled(true);
    } else {
        deleteSelectedItemAction->setEnabled(false);
    }
}

void MainWindow::graphInputOutputNodesChanged()
{
    if (m_scene->inputNode() && m_scene->outputNode()) {
        computeAction->setEnabled(true);
    } else {
        computeAction->setEnabled(false);
    }
}

void MainWindow::processFinished()
{
    enableWidgets();
    //TODO: Do more with the results
    statusBar()->showMessage(tr("Computation finished"), 3000);
}

void MainWindow::processError()
{
    enableWidgets();
    m_outputDockWidget->append(tr("    Backend error occurred!\n"));
    statusBar()->showMessage(tr("Backend error occurred!"), 5000);
}

void MainWindow::zoomToFit()
{
    m_view->zoomToFit();
    zoomToFitAction->setChecked(true);
    statusBar()->showMessage(tr("Zoomed to fit graph in view"), 2000);
}

void MainWindow::uncheckZoomToFitAction()
{
    zoomToFitAction->setChecked(false);
}

void MainWindow::checkForFirstStart()
{
    // Check if this is the first time we started the application
    QSettings settings;
    settings.beginGroup("general");
    if (settings.value("firstStart", true).toBool()) {
        on_configureAction_triggered();
    }
    settings.endGroup();
}

void MainWindow::disableWidgets()
{
    // File actions
    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);

    // Graph actions
    addColumnAction->setEnabled(false);
    addRowAction->setEnabled(false);
    removeColumnAction->setEnabled(false);
    removeRowAction->setEnabled(false);
    computeAction->setEnabled(false);

    // Settings actions
    configureAction->setEnabled(false);

    // Dock widgets
    m_editDockWidget->setEnabled(false);
    m_nodeDetailDockWidget->setEnabled(false);
}

void MainWindow::enableWidgets()
{
    // File actions
    saveAction->setEnabled(true);
    saveAsAction->setEnabled(true);

    // Graph actions
    addColumnAction->setEnabled(true);
    addRowAction->setEnabled(true);
    removeColumnAction->setEnabled(true);
    removeRowAction->setEnabled(true);
    computeAction->setEnabled(true);
    graphSelectionChanged();    // Call slot to determine state of other QActions

    // Settings actions
    configureAction->setEnabled(true);

    // Dock widgets
    m_editDockWidget->setEnabled(true);
    m_nodeDetailDockWidget->setEnabled(true);
}

void MainWindow::readSettings()
{
    QSettings settings;

    // Load window specific settings
    settings.beginGroup("mainwindow");
    resize(settings.value("size", QSize(800, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    restoreState(settings.value("windowState").toByteArray());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings;

    // Save window specific settings
    settings.beginGroup("mainwindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("windowState", saveState());
    settings.endGroup();
}

void MainWindow::setupActions()
{
    QStringList themeSearchPaths = QIcon::themeSearchPaths();
    themeSearchPaths << QDir::currentPath() + QDir::separator() + "data" +
                        QDir::separator() + "icons";
    QIcon::setThemeSearchPaths(themeSearchPaths);
    QIcon::setThemeName("oxygen-minimal");

    // Set icons for the actions in the file menu
    newAction->setIcon(QIcon::fromTheme("document-new"));
    loadAction->setIcon(QIcon::fromTheme("document-open"));
    saveAction->setIcon(QIcon::fromTheme("document-save"));
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as"));
    quitAction->setIcon(QIcon::fromTheme("application-exit"));

    // Set icons for the actions in the edit menu
    undoAction->setIcon(QIcon::fromTheme("edit-undo"));
    redoAction->setIcon(QIcon::fromTheme("edit-redo"));
    cutAction->setIcon(QIcon::fromTheme("edit-cut"));
    copyAction->setIcon(QIcon::fromTheme("edit-copy"));
    pasteAction->setIcon(QIcon::fromTheme("edit-paste"));

    zoomToFitAction->setIcon(QIcon::fromTheme("zoom-fit-best"));
    connect(zoomToFitAction, SIGNAL(triggered()), this, SLOT(zoomToFit()));
    zoomInAction->setIcon(QIcon::fromTheme("zoom-in"));
    connect(zoomInAction, SIGNAL(triggered()), m_view, SLOT(zoomIn()));
    zoomOutAction->setIcon(QIcon::fromTheme("zoom-out"));
    connect(zoomOutAction, SIGNAL(triggered()), m_view, SLOT(zoomOut()));

    // Set icons for the actions in the graph menu
    addColumnAction->setIcon(QIcon::fromTheme("edit-table-insert-column-right"));
    connect(addColumnAction, SIGNAL(triggered()), m_scene, SLOT(addColumn()));
    removeColumnAction->setIcon(QIcon::fromTheme("edit-table-delete-column"));
    connect(removeColumnAction, SIGNAL(triggered()), m_scene, SLOT(removeColumn()));
    addRowAction->setIcon(QIcon::fromTheme("edit-table-insert-row-below"));
    connect(addRowAction, SIGNAL(triggered()), m_scene, SLOT(addRow()));
    removeRowAction->setIcon(QIcon::fromTheme("edit-table-delete-row"));
    connect(removeRowAction, SIGNAL(triggered()), m_scene, SLOT(removeRow()));
    deleteSelectedItemAction->setIcon(QIcon::fromTheme("edit-delete"));
    connect(deleteSelectedItemAction, SIGNAL(triggered()),m_scene, SLOT(removeSelectedItem()));
    computeAction->setIcon(QIcon::fromTheme("system-run"));

    // Set icons for the actions in the settings menu
    configureAction->setIcon(QIcon::fromTheme("configure"));

    // Set icons for the actions in the help menu
    helpAction->setIcon(QIcon::fromTheme("help-contents"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
}

void MainWindow::setupDockWidgets()
{
    // Edit dock widget
    m_editDockWidget = new EditDockWidget(m_scene, this);
    connect(m_editDockWidget, SIGNAL(deleteSelectedItem()), m_scene, SLOT(removeSelectedItem()));
    addDockWidget(Qt::BottomDockWidgetArea, m_editDockWidget);
    dockersSettingsMenu->addAction(m_editDockWidget->toggleViewAction());

    // Node detail dock widget
    m_nodeDetailDockWidget = new NodeDetailDockWidget(m_scene, this);
    addDockWidget(Qt::BottomDockWidgetArea, m_nodeDetailDockWidget);
    dockersSettingsMenu->addAction(m_nodeDetailDockWidget->toggleViewAction());

    // Output dock widget
    m_outputDockWidget = new OutputDockWidget(m_process, this);
    addDockWidget(Qt::BottomDockWidgetArea, m_outputDockWidget);
    dockersSettingsMenu->addAction(m_outputDockWidget->toggleViewAction());
}

void MainWindow::setupToolbars()
{
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(loadAction);
    fileToolBar->addAction(saveAction);
    toolBarsSettingsMenu->addAction(fileToolBar->toggleViewAction());

    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    /*editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);*/
    toolBarsSettingsMenu->addAction(editToolBar->toggleViewAction());

    viewToolBar->addAction(zoomToFitAction);
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    toolBarsSettingsMenu->addAction(viewToolBar->toggleViewAction());

    graphToolBar->addAction(addColumnAction);
    graphToolBar->addAction(removeColumnAction);
    graphToolBar->addAction(addRowAction);
    graphToolBar->addAction(removeRowAction);
    graphToolBar->addAction(deleteSelectedItemAction);
    graphToolBar->addSeparator();
    graphToolBar->addAction(computeAction);
    toolBarsSettingsMenu->addAction(graphToolBar->toggleViewAction());
}

#include "mainwindow.moc"
