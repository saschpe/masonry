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

#include "gui/mainwindow.h"

#include <Quarter/Quarter.h>
#include <Quarter/QuarterWidget.h>

#include <QApplication>

#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>

using namespace SIM::Coin3D::Quarter;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*MainWindow win;
    win.show();*/

    Quarter::init();

    SoSeparator *root = new SoSeparator;
    root->ref();

    SoBaseColor *col = new SoBaseColor;
    col->rgb = SbColor(1, 1, 0);
    root->addChild(col);
    root->addChild(new SoCone);

    QuarterWidget *viewer = new QuarterWidget;
    viewer->setSceneGraph(root);
    viewer->setNavigationModeFile(QUrl("coin:///scxml/navigation/examiner.xml"));
    viewer->show();

    app.exec();

    root->unref();
    delete viewer;
    Quarter::clean();

    return 0;
}
