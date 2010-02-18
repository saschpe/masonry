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

#include "configdialog.h"

#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>
#include <QLatin1String>
#include <QPushButton>
#include <QSettings>

#ifdef Q_OS_WIN32
const QLatin1String MATLAB_EXECUTABLE("matlab.exe");
const QLatin1String OCTAVE_EXECUTABLE("octave.exe");
#else
const QLatin1String MATLAB_EXECUTABLE("matlab");
const QLatin1String OCTAVE_EXECUTABLE("octave");
#endif

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    groupListWidget->item(0)->setIcon(QIcon::fromTheme("go-home"));
    groupListWidget->item(1)->setIcon(QIcon::fromTheme("view-choose"));
    groupListWidget->item(2)->setIcon(QIcon::fromTheme("system-run"));

    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(clicked(QAbstractButton *)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    readSettings();
}

void ConfigDialog::on_octaveExecutableChooseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Please Select Octave Executable"),
        QDir::rootPath(),
        tr("Octave Executable (%1)").arg(OCTAVE_EXECUTABLE));
    if (!fileName.isEmpty()) {
        octaveExecutableLineEdit->setText(fileName);
    }
}

void ConfigDialog::on_matlabExecutableChooseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Please Select Matlab Executable"),
        QDir::rootPath(),
        tr("Matlab Executable (%1)").arg(MATLAB_EXECUTABLE));
    if (!fileName.isEmpty()) {
        matlabExecutableLineEdit->setText(fileName);
    }
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

    settings.beginGroup("backend");
    if (settings.value("current", "octave").toString() == "octave") {
        backendComboBox->setCurrentIndex(0);
    } else {
        backendComboBox->setCurrentIndex(1);
    }
    settings.beginGroup("octave");
    octaveExecutableLineEdit->setText(settings.value("executable", OCTAVE_EXECUTABLE).toString());
    octaveParameterLineEdit->setText(settings.value("parameters", "--silent --path \"" + QDir::toNativeSeparators("data/scripts") + "\" --eval \"%1;\"").toString());
    settings.endGroup();
    settings.beginGroup("matlab");
    matlabExecutableLineEdit->setText(settings.value("executable", MATLAB_EXECUTABLE).toString());
    matlabParameterLineEdit->setText(settings.value("parameters", "-nosplash -nodisplay -nojvm -r \"addpath('" + QDir::toNativeSeparators("data/scripts") + "');%1;exit\"").toString());
    settings.endGroup();
    settings.endGroup();
}

void ConfigDialog::writeSettings()
{
    QSettings settings;

    settings.beginGroup("general");
    settings.setValue("firstStart", false);
    settings.endGroup();

    settings.beginGroup("backend");
    if (backendComboBox->currentText().contains("Octave")) {
        settings.setValue("current", "octave");
    } else {
        settings.setValue("current", "matlab");
    }
    settings.beginGroup("octave");
    settings.setValue("executable", octaveExecutableLineEdit->text());
    settings.setValue("parameters", octaveParameterLineEdit->text());
    settings.endGroup();
    settings.beginGroup("matlab");
    settings.setValue("executable", matlabExecutableLineEdit->text());
    settings.setValue("parameters", matlabParameterLineEdit->text());
    settings.endGroup();
    settings.endGroup();
}

#include "configdialog.moc"
