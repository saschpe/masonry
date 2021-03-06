/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sascha@peilicke.de>

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
    groupListWidget->item(1)->setIcon(QIcon::fromTheme("system-run"));
    addCustomScriptButton->setIcon(QIcon::fromTheme("list-add"));
    removeCustomScriptButton->setIcon(QIcon::fromTheme("list-remove"));

    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(clicked(QAbstractButton *)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(customScriptListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(customScriptRowChanged()));

    readSettings();
}

void ConfigDialog::on_octaveExecutableChooseButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this,
        tr("Please Select Octave Executable"),
        QDir::rootPath(),
        tr("Octave Executable (%1)").arg(OCTAVE_EXECUTABLE));
    if (!fileName.isEmpty()) {
        octaveExecutableLineEdit->setText(fileName);
    }
}

void ConfigDialog::on_matlabExecutableChooseButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this,
        tr("Please Select Matlab Executable"),
        QDir::rootPath(),
        tr("Matlab Executable (%1)").arg(MATLAB_EXECUTABLE));
    if (!fileName.isEmpty()) {
        matlabExecutableLineEdit->setText(fileName);
    }
}

void ConfigDialog::on_addCustomScriptButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this,
        tr("Add Matlab Script File"),
        QDir::currentPath() + QDir::separator() + "data" + QDir::separator() + "scripts",
        tr("Matlab Script Files") + QLatin1String(" (*.m)"));
    if (!fileName.isEmpty()) {
        customScriptListWidget->addItem(fileName);
    }
}

void ConfigDialog::on_removeCustomScriptButton_clicked()
{
    customScriptListWidget->takeItem(customScriptListWidget->currentRow());
}

void ConfigDialog::customScriptRowChanged()
{
    removeCustomScriptButton->setEnabled(customScriptListWidget->currentRow() != -1);
}

void ConfigDialog::clicked(QAbstractButton *button)
{
    if (button == buttonBox->button(QDialogButtonBox::Ok)) {
        writeSettings();
    } else if (button == buttonBox->button(QDialogButtonBox::Reset)) {
        QSettings settings;
        settings.clear();
        readSettings();
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
    matlabParameterLineEdit->setText(settings.value("parameters", "-nosplash -nodisplay -nodesktop -r \"addpath('" + QDir::toNativeSeparators("data/scripts") + "');%1;exit\"").toString());
    settings.endGroup();
    settings.endGroup();

    settings.beginGroup("customScripts");
    foreach (const QString &key, settings.allKeys()) {
        const QString scriptFileName = settings.value(key).toString();
        if (QFile(scriptFileName).exists()) {
            customScriptListWidget->addItem(scriptFileName);
        }
    }
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

    const int count = customScriptListWidget->count();
    if (count > 0) {
        settings.beginGroup("customScripts");
        settings.remove("");                    // Clear current group
        for (int i = 0; i < count; i++) {
            const QString scriptFileName = customScriptListWidget->item(i)->text();
            if (QFile(scriptFileName).exists()) {
                settings.setValue("script" + QString::number(i), scriptFileName);
            }
        }
        settings.endGroup();
    }
}

#include "configdialog.moc"
