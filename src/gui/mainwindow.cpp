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
#include "widgets/infodockwidget.h"
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
    , m_graphChangesUnsaved(false), m_lastSelectedNodeItem(NULL)
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
    connect(m_view, SIGNAL(zoomChanged()), this, SLOT(uncheckZoomToFitAction()));

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
        QString fileName = QFileDialog::getOpenFileName(this,
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
    QString fileName = QFileDialog::getSaveFileName(this,
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
    // Remove old temporary file and create a new one
    delete m_backendInputFile;
    m_backendInputFile = new QTemporaryFile;

    if (m_backendInputFile->open()) {
        QTextStream stream(m_backendInputFile);

        m_outputDockWidget->clear();
        m_outputDockWidget->append("Input:\n\n");

        // Generate backend input file contents
        int counter = 0;
        foreach (DirectedEdgeItem *edge, m_scene->edges()) {
            // NOTE: This is rather hacky and should be encapsulated in the GraphScene class.
            if (edge->name().isEmpty()) {
                continue;
            }
            QString from = edge->start()->name();
            QString to = edge->end()->name();

            QString line = QString::number(counter++) + ' ' + from + ' ' + to + ' ' + edge->name() + '\n';
            m_outputDockWidget->append("    " + line);
            stream << line;
        }
        int startNodeNumber = m_lastSelectedNodeItem->name().toInt();
        int stopNodeNumber = m_scene->nodes().size() - 1; // It's the second last node in the list
        m_backendInputFile->close();

        // Create call to 'mason' script with supplied arguments
        QString mscript = QString("mason('%1',%2,%3)")
            .arg(m_backendInputFile->fileName())
            .arg(startNodeNumber).arg(stopNodeNumber);

        QString backend;
        QSettings settings;
        settings.beginGroup("backend");
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

        // Start the backend process
        m_outputDockWidget->append("\nCommand Line:\n\n    " + backend.arg(mscript) + "\n");
        m_outputDockWidget->append("\nResults:\n\n");
        m_process->start(backend.arg(mscript));
        statusBar()->showMessage(tr("Compute response for node '%1'...").arg(m_lastSelectedNodeItem->name()));
    } else {
        statusBar()->showMessage(tr("Unable to create temporary file!"), 3000);
    }
}

void MainWindow::on_configureAction_triggered()
{
    ConfigDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        readSettings();
        m_scene->readSettings();
    }
    statusBar()->showMessage(tr("Settings saved"), 2000);
}

void MainWindow::on_helpAction_triggered()
{
    // "TODO: Show help";
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
    m_graphChangesUnsaved = true;
    removeLayerAction->setEnabled(m_scene->layers().size() > 0);
}

void MainWindow::graphSelectionChanged()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() == 1) {
        if (m_lastSelectedNodeItem = dynamic_cast<NodeItem *>(selection.first())) {
            computeAction->setEnabled(true);
        } else {
            computeAction->setEnabled(false);
        }
    } else {
        m_lastSelectedNodeItem = NULL;
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
    //TODO: Handle error
    statusBar()->showMessage(tr("Backend error occurred!"), 3000);
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
    addLayerAction->setEnabled(false);
    removeLayerAction->setEnabled(false);
    computeAction->setEnabled(false);

    // Settings actions
    configureAction->setEnabled(false);

    // Edit dock widget
    m_editDockWidget->setEnabled(false);
}

void MainWindow::enableWidgets()
{
    // File actions
    saveAction->setEnabled(true);
    saveAsAction->setEnabled(true);

    // Graph actions
    addLayerAction->setEnabled(true);
    removeLayerAction->setEnabled(true);
    graphSelectionChanged();    // Call slot to determine state of computeAction

    // Settings actions
    configureAction->setEnabled(true);

    // Edit dock widget
    m_editDockWidget->setEnabled(true);
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
    QIcon::setThemeName("oxygen");

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
    addLayerAction->setIcon(QIcon::fromTheme("list-add"));
    connect(addLayerAction, SIGNAL(triggered()), m_scene, SLOT(addLayer()));
    removeLayerAction->setIcon(QIcon::fromTheme("list-remove"));
    connect(removeLayerAction, SIGNAL(triggered()), m_scene, SLOT(removeLayer()));
    computeAction->setIcon(QIcon::fromTheme("system-run"));

    // Set icons for the actions in the settings menu
    configureAction->setIcon(QIcon::fromTheme("configure"));

    // Set icons for the actions in the help menu
    helpAction->setIcon(QIcon::fromTheme("help-contents"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
}

void MainWindow::setupDockWidgets()
{
    // Info dock widget
    QDockWidget *infoDockWidget = new InfoDockWidget(m_scene, this);
    addDockWidget(Qt::BottomDockWidgetArea, infoDockWidget);
    dockersSettingsMenu->addAction(infoDockWidget->toggleViewAction());

    // Edit dock widget
    m_editDockWidget = new EditDockWidget(m_scene, this);
    addDockWidget(Qt::BottomDockWidgetArea, m_editDockWidget);
    //dockersSettingsMenu->addAction(m_editDockWidget->toggleViewAction());

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
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    toolBarsSettingsMenu->addAction(editToolBar->toggleViewAction());

    viewToolBar->addAction(zoomToFitAction);
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    toolBarsSettingsMenu->addAction(viewToolBar->toggleViewAction());

    graphToolBar->addAction(addLayerAction);
    graphToolBar->addAction(removeLayerAction);
    graphToolBar->addAction(computeAction);
    toolBarsSettingsMenu->addAction(graphToolBar->toggleViewAction());
}

#include "mainwindow.moc"
