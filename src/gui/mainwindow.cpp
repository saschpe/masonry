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

#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_graphScene(new GraphScene), m_graphView(new GraphView(m_graphScene))
{
    setupUi(this);

    setCentralWidget(m_graphView);

    loadPreferences();
    setupActions();
    setupDockWidgets();
    setupToolbars();
}

MainWindow::~MainWindow()
{
    savePreferences();
    delete m_graphScene;
    delete m_graphView;
}

void MainWindow::loadPreferences()
{

}

void MainWindow::savePreferences()
{

}

void MainWindow::setupActions()
{

}

void MainWindow::setupDockWidgets()
{

}

void MainWindow::setupToolbars()
{
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(loadAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->setVisible(showFileToolBarAction->isChecked());

    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    /*editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);*/
    editToolBar->setVisible(showEditToolBarAction->isChecked());

    graphToolBar->addAction(addGraphNodeAction);
    graphToolBar->addAction(addGraphEdgeAction);
    graphToolBar->addAction(removeGraphItemAction);
    graphToolBar->setVisible(showGraphToolBarAction->isChecked());
}

#include "mainwindow.moc"
