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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>

class GraphScene;
class GraphView;
class NodeItem;
class OutputDockWidget;

class QDockWidget;
class QProcess;
class QTemporaryFile;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_newAction_triggered();
    void on_loadAction_triggered();
    void on_saveAction_triggered();
    void on_saveAsAction_triggered();
    void on_computeAction_triggered();
    void on_configureAction_triggered();
    void on_helpAction_triggered();
    void on_aboutAction_triggered();
    void on_aboutQtAction_triggered();
    void graphChanged();
    void graphSelectionChanged();
    void processFinished();
    void processError();

    void zoomToFit();
    void uncheckZoomToFitAction();
    void checkForFirstStart();
    void disableWidgets();
    void enableWidgets();

    void readSettings();
    void writeSettings();

private:
    int checkForUnsavedChanges();
    void setupActions();
    void setupDockWidgets();
    void setupToolbars();

    GraphScene *m_scene;
    GraphView *m_view;

    QDockWidget *m_editDockWidget;
    OutputDockWidget *m_outputDockWidget;

    QProcess *m_process;
    QTemporaryFile *m_backendInputFile;

    bool m_graphChangesUnsaved;
    QString m_lastFileName;
    NodeItem *m_lastSelectedNodeItem;
};

#endif // MAINWINDOW_H
