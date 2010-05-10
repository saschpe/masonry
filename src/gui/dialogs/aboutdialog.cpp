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

#include "aboutdialog.h"

#include <QCoreApplication>
#include <QDir>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setWindowIcon(QIcon(QString(MASONRY_ICON_DIR) + QDir::separator() + "hicolor" +
                        QDir::separator() + "32x32" + QDir::separator() + "apps" +
                        QDir::separator() + "masonry.png"));

    QUrl url = QUrl("http://" + QCoreApplication::organizationDomain());

    organizationLabel->setOpenExternalLinks(true);
    organizationLabel->setText(tr("<strong>%1 e.V.</strong> (<a href=\"%2\">%2</a>)").arg(QCoreApplication::organizationName()).arg(url.toString()));
    versionLabel->setText(tr("Version %1").arg(QCoreApplication::applicationVersion()));
    pictureLabel->setPixmap(QPixmap(QString(MASONRY_ICON_DIR) + QDir::separator() + "hicolor" +
                                    QDir::separator() + "128x128" + QDir::separator() + "apps" +
                                    QDir::separator() + "masonry.png"));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

#include "aboutdialog.moc"
