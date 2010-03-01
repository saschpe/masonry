/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sasch.pe@gmx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "ui_configdialog.h"

#include <QDialog>

class ConfigDialog : public QDialog, private Ui::ConfigDialog
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = 0);

private slots:
    void on_octaveExecutableChooseButton_clicked();
    void on_matlabExecutableChooseButton_clicked();
    void on_addCustomScriptButton_clicked();
    void on_removeCustomScriptButton_clicked();
    void customScriptRowChanged();
    void clicked(QAbstractButton *);

    void readSettings();
    void writeSettings();
};

#endif // CONFIGDIALOG_H
