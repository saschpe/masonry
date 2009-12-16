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

#include "aboutdialog.h"

#include <QCoreApplication>
#include <QDebug>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QUrl url = QUrl("http://" + QCoreApplication::organizationDomain());

    organizationLabel->setText(tr("%1 e.V. (%2)").arg(QCoreApplication::organizationName()).arg(url.toString()));
    versionLabel->setText(tr("Version %1").arg(QCoreApplication::applicationVersion()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

#include "aboutdialog.moc"
