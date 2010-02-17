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

class ArrowItem;
class DirectedEdgeItem;
class NodeItem;
class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum InitType {
        EmptyInit,
        StandardInit
    };

    GraphScene(QObject *parent = 0);

    bool loadFrom(const QString &fileName);
    bool saveTo(const QString &fileName);

    bool addEdge(NodeItem *start, NodeItem *end);

    void setInputNode(NodeItem *node);
    NodeItem *inputNode() const { return m_inputNode; }
    void setOuputNode(NodeItem *node);
    NodeItem *outputNode() const { return m_outputNode; }

    QList<DirectedEdgeItem *> edges() const { return m_edges; }
    int columnCount() const;
    int rowCount() const;

    NodeItem *selectedNode() const;
    DirectedEdgeItem *selectedEdge() const;

signals:
    void graphChanged();
    void inputNodeChanged();
    void outputNodeChanged();

public slots:
    void init(InitType initType = StandardInit);

    void addRow();
    void removeRow();
    void addColumn();
    void removeColumn();
    void removeSelectedItem();
    void removeItem(QGraphicsItem *item);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void updateNodeItemNames();

    QGraphicsGridLayout *m_gridLayout;
    QList<DirectedEdgeItem *> m_edges;

    bool m_inDrag;
    ArrowItem *m_dragArrow;
    NodeItem *m_dragStartNode;
    NodeItem *m_inputNode;
    NodeItem *m_outputNode;
};

#endif // GRAPHSCENE_H
