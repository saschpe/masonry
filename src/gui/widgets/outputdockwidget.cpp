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

#include "outputdockwidget.h"

#include <QProcess>

OutputDockWidget::OutputDockWidget(QProcess *process, QWidget *parent)
    : QDockWidget(parent), m_process(process)
{
    setupUi(this);

    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(readStandardError()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()));
}

void OutputDockWidget::clear()
{
    outputTextEdit->clear();
}

void OutputDockWidget::append(const QString &output)
{
    outputTextEdit->setText(outputTextEdit->toPlainText() + output);
}

void OutputDockWidget::readStandardError()
{
    outputTextEdit->setText(outputTextEdit->toPlainText() + m_process->readAllStandardError());
}

void OutputDockWidget::readStandardOutput()
{
    outputTextEdit->setText(outputTextEdit->toPlainText() + m_process->readAllStandardOutput());
}

#include "outputdockwidget.moc"
