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

#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class ArrowItem;
class DirectedEdgeItem;
class NodeItem;
class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;

/**
 * The GraphScene class represents the entire scene in which
 * the Mason graph is contained. It is responsible for loading
 * and saving graph files and is the parent of all nodes and edges. It does some related house-keeping and provides scene interaction (like drag'n'drop support).
 */
class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum InitType {
        EmptyInit,
        StandardInit
    };

    GraphScene(QObject *parent = 0);

    void init(InitType initType = StandardInit);
    bool loadFrom(const QString &fileName);
    bool saveTo(const QString &fileName);

    DirectedEdgeItem *addEdge(NodeItem *start, NodeItem *end);
    QList<DirectedEdgeItem *> edges() const { return m_edges; }

    void setInputNode(NodeItem *node);
    NodeItem *inputNode() const { return m_inputNode; }
    void setOuputNode(NodeItem *node);
    NodeItem *outputNode() const { return m_outputNode; }

    int columnCount() const;
    int rowCount() const;

    NodeItem *selectedNode() const;
    DirectedEdgeItem *selectedEdge() const;

signals:
    void graphChanged();
    void inputNodeChanged();
    void outputNodeChanged();

public slots:
    void addRow();
    void removeRow();
    void addColumn();
    void removeColumn();
    void removeSelectedItem();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void removeItem(QGraphicsItem *item);
    void updateItemNames();

    QGraphicsGridLayout *m_gridLayout;
    QList<DirectedEdgeItem *> m_edges;

    bool m_inDrag;
    ArrowItem *m_dragArrow;
    NodeItem *m_dragStartNode;
    NodeItem *m_inputNode;
    NodeItem *m_outputNode;
};

#endif // GRAPHSCENE_H
