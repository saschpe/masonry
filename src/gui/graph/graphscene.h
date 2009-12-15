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

#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class DirectedEdgeItem;
class NodeItem;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {
        InsertNode = 1,
        InsertDirectedEdge,
        MoveItem,
    };

    GraphScene(QObject *parent = 0);
    virtual ~GraphScene();

    void addItem(NodeItem *);
    void addItem(DirectedEdgeItem *);

    QList<NodeItem *> nodes() const { return m_nodes; }
    QList<DirectedEdgeItem *> edges() const { return m_edges; }

public slots:
    void setMode(Mode mode);

signals:
    void edgeInserted(DirectedEdgeItem *);
    void nodeInserted(NodeItem *);
    void itemInserted(QGraphicsItem *);

protected:
    /*void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);*/

private:
    QList<NodeItem *> m_nodes;
    QList<DirectedEdgeItem *> m_edges;
};

#endif // GRAPHSCENE_H
