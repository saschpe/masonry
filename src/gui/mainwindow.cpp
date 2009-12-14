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
#include "configdialog.h"
#include "graph/directededgeitem.h"
#include "graph/nodeitem.h"
#include "graph/graphscene.h"
#include "graph/graphview.h"
#include "widgets/infodockwidget.h"
#include "widgets/outputdockwidget.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDockWidget>
#include <QSettings>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_graphScene(new GraphScene), m_graphView(new GraphView(m_graphScene))
{
    setupUi(this);
    setCentralWidget(m_graphView);

    NodeItem *node1 = new NodeItem;
    node1->setPos(100, 0);
    node1->setName("1");
    node1->setIsOutput(true);
    NodeItem *node2 = new NodeItem;
    node2->setPos(0, 10);
    node2->setName("2");
    NodeItem *node3 = new NodeItem("3");
    node3->setPos(-100, 50);
    node3->setRadius(20);
    node3->setIsInput(true);
    DirectedEdgeItem *edge1 = new DirectedEdgeItem(node1, node2, "a");
    DirectedEdgeItem *edge2 = new DirectedEdgeItem(node2, node3, "b");

    m_graphScene->addItem(node1);
    m_graphScene->addItem(node2);
    m_graphScene->addItem(node3);
    m_graphScene->addItem(edge1);
    m_graphScene->addItem(edge2);

    setupActions();
    setupDockWidgets();
    setupToolbars();
    readSettings();
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
    qDebug() << "Run computation of Mason graph...";
    //TODO: Convert graph into suitable representation
    //      and feed it to Matlab/Octave/...
}

void MainWindow::on_configureAction_triggered()
{
    ConfigDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_helpAction_triggered()
{
    qDebug() << "TODO: Show help";
}

void MainWindow::on_aboutAction_triggered()
{
    qDebug() << "TODO: Show about screen";
}

void MainWindow::on_aboutQtAction_triggered()
{
    QApplication::aboutQt();
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
    themeSearchPaths << "data/icons";
    QIcon::setThemeSearchPaths(themeSearchPaths);
    QIcon::setThemeName("oxygen");
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
    deleteAction->setIcon(QIcon::fromTheme("edit-delete"));
    selectAllAction->setIcon(QIcon::fromTheme("edit-select-all"));

    // Set icons for the actions in the graph menu
    addGraphNodeAction->setIcon(QIcon::fromTheme("format-add-node"));
    addGraphEdgeAction->setIcon(QIcon::fromTheme("format-add-node"));

    // Set icons for the actions in the settings menu
    configureAction->setIcon(QIcon::fromTheme("configure"));

    // Set icons for the actions in the help menu
    helpAction->setIcon(QIcon::fromTheme("help-contents"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
}

void MainWindow::setupDockWidgets()
{
    // Info dock widget
    m_infoDockWidget = new InfoDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, m_infoDockWidget);
    dockersSettingsMenu->addAction(m_infoDockWidget->toggleViewAction());

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
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(selectAllAction);
    toolBarsSettingsMenu->addAction(editToolBar->toggleViewAction());

    graphToolBar->addAction(addGraphNodeAction);
    graphToolBar->addAction(addGraphEdgeAction);
    toolBarsSettingsMenu->addAction(graphToolBar->toggleViewAction());
}

#include "mainwindow.moc"
