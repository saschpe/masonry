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

#include <QApplication>

#include <iostream>
#include <tulip/Graph.h>

using namespace std;
using namespace tlp;

int main(int argc, char *argv[])
{
    Graph *graph = tlp::newGraph();

    node n1 = graph->addNode();
    node n2 = graph->addNode();
    node n3 = graph->addNode();

    edge e1 = graph->addEdge(n2, n3);
    edge e2 = graph->addEdge(n1, n2);
    edge e3 = graph->addEdge(n3, n1);

    cout << graph << flush;
    tlp::saveGraph(graph, "tuto1.tlp");

    delete graph;
    return EXIT_SUCCESS;


    /*QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();*/
}
