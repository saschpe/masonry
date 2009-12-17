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

#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphScene(QObject *parent = 0);

    void loadFrom(const QString &fileName);
    void saveTo(const QString &fileName);

    int layerCount() const;
    int nodeCount() const;
    int edgeCount() const;

signals:
    void graphChanged();

public slots:
    void init();
    void readSettings();
    void addLayer();
    void removeLayer();
};

#endif // GRAPHSCENE_H
