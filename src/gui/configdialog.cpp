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

#include "configdialog.h"

#include <QCloseEvent>
#include <QPushButton>
#include <QSettings>

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    listWidget->item(0)->setIcon(QIcon::fromTheme("go-home"));
    listWidget->item(1)->setIcon(QIcon::fromTheme("view-choose"));
    listWidget->item(2)->setIcon(QIcon::fromTheme("system-run"));

    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(clicked(QAbstractButton *)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    readSettings();
}

void ConfigDialog::clicked(QAbstractButton *button)
{
    if (button == buttonBox->button(QDialogButtonBox::Ok)) {
        writeSettings();
    } else if (button == buttonBox->button(QDialogButtonBox::Reset)) {
        QSettings settings;
        settings.clear();
    }
}

void ConfigDialog::readSettings()
{
    QSettings settings;

    settings.beginGroup("general");
    settings.endGroup();

    settings.beginGroup("view");
    settings.endGroup();

    settings.beginGroup("backend");
    settings.endGroup();
}

void ConfigDialog::writeSettings()
{
    QSettings settings;

    settings.beginGroup("general");
    settings.endGroup();

    settings.beginGroup("view");
    settings.endGroup();

    settings.beginGroup("backend");
    settings.endGroup();
}

#include "configdialog.moc"
