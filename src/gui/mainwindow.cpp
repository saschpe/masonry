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
#include "graphicsview/graphscene.h"
#include "graphicsview/graphview.h"

#include <QCloseEvent>
#include <QDebug>
#include <QSettings>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_graphScene(new GraphScene), m_graphView(new GraphView(m_graphScene))
{
    setupUi(this);

    setCentralWidget(m_graphView);

    setupActions();
    setupDockWidgets();
    setupToolbars();

    readSettings();

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete m_graphScene;
    delete m_graphView;
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

void MainWindow::on_saveAsAction_triggered()
{
    qDebug() << "Save graph";
}

void MainWindow::on_helpAction_triggered()
{
    qDebug() << "TODO: Show help";
}

void MainWindow::on_aboutAction_triggered()
{
    qDebug() << "TODO: Show about screen";
}

void MainWindow::readSettings()
{
    QSettings settings;

    // Load window specific settings
    settings.beginGroup("mainwindow");
    resize(settings.value("size", QSize(800, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    // Load view specific settings
    settings.beginGroup("view");
    showFileToolBarAction->setChecked(settings.value("showFileToolBar", true).toBool());
    showEditToolBarAction->setChecked(settings.value("showEditToolBar", true).toBool());
    showGraphToolBarAction->setChecked(settings.value("showGraphToolBar", true).toBool());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings;

    // Save window specific settings
    settings.beginGroup("mainwindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    // Save view specific settings
    settings.beginGroup("view");
    settings.setValue("showFileToolBar", showFileToolBarAction->isChecked());
    settings.setValue("showEditToolBar", showEditToolBarAction->isChecked());
    settings.setValue("showGraphToolBar", showGraphToolBarAction->isChecked());
    settings.endGroup();
}

bool MainWindow::maybeSave()
{
    //TODO: If graph has unsafed modifications return false
    return true;
}

void MainWindow::setupActions()
{
#ifndef QT_WS_X11
    // Set a specific icon theme on non-X11 platforms.
    QStringList themeSearchPaths = QIcon::themeSearchPaths();
    themeSearchPaths << "data/icons";
    QIcon::setThemeSearchPaths(themeSearchPaths);
    QIcon::setThemeName("oxygen");
#endif

    // Set icons for the actions in the file menu
    newAction->setIcon(QIcon::fromTheme("document-new"));
    loadAction->setIcon(QIcon::fromTheme("document-open"));
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as"));
    quitAction->setIcon(QIcon::fromTheme("application-exit"));

    // Set icons for the actions in the edit menu
    undoAction->setIcon(QIcon::fromTheme("edit-undo"));
    redoAction->setIcon(QIcon::fromTheme("edit-redo"));
    cutAction->setIcon(QIcon::fromTheme("edit-cut"));
    copyAction->setIcon(QIcon::fromTheme("edit-copy"));
    pasteAction->setIcon(QIcon::fromTheme("edit-paste"));
    selectAllAction->setIcon(QIcon::fromTheme("edit-select-all"));

    // Set icons for the actions in the graph menu
    addGraphNodeAction->setIcon(QIcon::fromTheme("format-add-node"));
    addGraphEdgeAction->setIcon(QIcon::fromTheme("format-add-node"));
    removeGraphItemAction->setIcon(QIcon::fromTheme("format-remove-node"));

    // Set icons for the actions in the settings menu
    preferencesAction->setIcon(QIcon::fromTheme("configure"));

    // Set icons for the actions in the help menu
    helpAction->setIcon(QIcon::fromTheme("help-contents"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
}

void MainWindow::setupDockWidgets()
{

}

void MainWindow::setupToolbars()
{
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(loadAction);
    fileToolBar->addAction(saveAsAction);
    fileToolBar->setVisible(showFileToolBarAction->isChecked());

    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->setVisible(showEditToolBarAction->isChecked());

    graphToolBar->addAction(addGraphNodeAction);
    graphToolBar->addAction(addGraphEdgeAction);
    graphToolBar->addAction(removeGraphItemAction);
    graphToolBar->setVisible(showGraphToolBarAction->isChecked());
}

#include "mainwindow.moc"
