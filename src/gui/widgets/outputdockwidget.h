/*
    Copyright (c) 2009 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009 Sascha Peilicke <sascha@peilicke.de>

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

#ifndef OUTPUTDOCKWIDGET_H
#define OUTPUTDOCKWIDGET_H

#include "ui_outputdockwidget.h"

#include <QDockWidget>

class QProcess;

/**
 * This dock widget can be used to show textual output of an application.
 * It is used here to display the results computed by the application backend
 * (like Matlab or Octave).
 *
 * @author Sascha Peilicke <sascha@peilicke.de>
 * @since 0.1
 */
class OutputDockWidget : public QDockWidget, private Ui::OutputDockWidget
{
    Q_OBJECT

public:
    OutputDockWidget(QProcess *process, QWidget *parent = 0);

public slots:
    void clear();
    void append(const QString &);

private slots:
    void readStandardError();
    void readStandardOutput();

private:
    QProcess *m_process;
};

#endif // OUTPUTDOCKWIDGET_H
