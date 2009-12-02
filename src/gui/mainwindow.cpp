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
#include "ui_mainwindow.h"

#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setupActions();
    setupToolbars();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::setupActions()
{

}

void MainWindow::setupToolbars()
{
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(m_ui->newAction);
    fileToolBar->addAction(m_ui->loadAction);
    fileToolBar->addAction(m_ui->saveAction);

    QToolBar *editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(m_ui->undoAction);
    editToolBar->addAction(m_ui->redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(m_ui->cutAction);
    editToolBar->addAction(m_ui->copyAction);
    editToolBar->addAction(m_ui->pasteAction);

    QToolBar *viewToolBar = addToolBar(tr("View"));
}

#include "mainwindow.moc"
