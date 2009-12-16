/*
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
#include "widgets/editdockwidget.h"
#include "widgets/infodockwidget.h"
#include "widgets/outputdockwidget.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDockWidget>
#include <QSettings>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_scene(new GraphScene), m_view(new GraphView(m_scene))
{
    setupUi(this);
    setCentralWidget(m_view);

    setupActions();
    setupDockWidgets();
    setupToolbars();
    readSettings();

    connect(m_view, SIGNAL(zoomChanged()), this, SLOT(uncheckZoomToFitAction()));
    //TODO: Implement this somehow:
    //connect(m_view, SIGNAL(selectionChanged()), this, SLOT(graphSelectionChanged()));

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_newAction_triggered()
{
    qDebug() << "New graph";
}

void MainWindow::on_loadAction_triggered()
{
    qDebug() << "Load graph";
}

void MainWindow::on_saveAction_triggered()
{
    qDebug() << "Save graph";
}

void MainWindow::on_saveAsAction_triggered()
{
    qDebug() << "Save graph as...";
}

void MainWindow::on_computeAction_triggered()
{
    statusBar()->showMessage(tr("Running Mason-graph computation ..."));
    qDebug() << "Run computation of Mason graph...";
    //TODO: Convert graph into suitable representation
    //      and feed it to Matlab/Octave/...
    statusBar()->showMessage(tr("Done"), 3000);
}

void MainWindow::on_configureAction_triggered()
{
    ConfigDialog dialog(this);
    dialog.exec();
    readSettings();
}

void MainWindow::on_helpAction_triggered()
{
    qDebug() << "TODO: Show help";
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

void MainWindow::zoomToFit()
{
    m_view->zoomToFit();
    zoomToFitAction->setChecked(true);
    statusBar()->showMessage(tr("Zoomed to fit Mason-graph in view."), 2000);
}
void MainWindow::uncheckZoomToFitAction()
{
    zoomToFitAction->setChecked(false);
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

bool MainWindow::maybeSave()
{
    //TODO: If graph has unsafed modifications return false
    return true;
}

void MainWindow::setupActions()
{
#ifndef Q_WS_X11
    // Set a specific icon theme on non-X11 platforms.
    QStringList themeSearchPaths = QIcon::themeSearchPaths();
    themeSearchPaths << QDir::currentPath() + QDir::separator() + "data" + QDir::separator() + "icons";
    QIcon::setThemeSearchPaths(themeSearchPaths);
    QIcon::setThemeName("oxygen");
    qDebug() << "Non-X11 specfic theme path:" << themeSearchPaths;
#endif

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
    removeLayerAction->setIcon(QIcon::fromTheme("list-remove"));
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
    m_infoDockWidget = new InfoDockWidget(m_scene, this);
    addDockWidget(Qt::RightDockWidgetArea, m_infoDockWidget);
    dockersSettingsMenu->addAction(m_infoDockWidget->toggleViewAction());

    // Edit dock widget
    m_editDockWidget = new EditDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, m_editDockWidget);
    //dockersSettingsMenu->addAction(m_editDockWidget->toggleViewAction());

    // Output dock widget
    m_outputDockWidget = new OutputDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, m_outputDockWidget);
    dockersSettingsMenu->addAction(m_outputDockWidget->toggleViewAction());
}

void MainWindow::setupToolbars()
{
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(loadAction);
    fileToolBar->addAction(saveAsAction);
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
