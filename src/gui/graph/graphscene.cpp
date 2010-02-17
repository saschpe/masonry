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

#include "graphscene.h"
#include "items/arrowitem.h"
#include "items/directededgeitem.h"
#include "items/nodeitem.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QPainter>
#include <QGraphicsGridLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QSettings>
#include <QTextStream>

static const int NODEITEM_PIXEL_DISTANCE = 50;

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_inDrag(false), m_dragArrow(NULL), m_dragStartNode(NULL)
    , m_inputNode(NULL), m_outputNode(NULL)
{
    setBackgroundBrush(Qt::white);

    init(StandardInit);
}

bool GraphScene::loadFrom(const QString &fileName)
{
    QFile file(fileName);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QHash<QString, NodeItem *> nodes;       // Temporary QHash for faster NodeItem lookup

        init(EmptyInit);

        // Iterate over all the lines in the file
        QString line;
        do {
            line = stream.readLine();
            const QStringList splittedLine = line.split(" ");
            if (splittedLine[0] == "node") {
                NodeItem *node = new NodeItem(NULL, this);
                node->setName(splittedLine[1]);
                node->setNodeType(static_cast<NodeItem::NodeType>(splittedLine[2].toInt()));

                nodes.insert(node->name(), node);
                m_gridLayout->addItem(node, splittedLine[3].toInt(), splittedLine[4].toInt());
            } else if (splittedLine[0] == "edge") {
                NodeItem *start = nodes[splittedLine[2]];
                NodeItem *end = nodes[splittedLine[3]];

                DirectedEdgeItem *edge = new DirectedEdgeItem(start, end, NULL, this);
                edge->setName(splittedLine[1]);
                m_edges.append(edge);
            }
        } while (!line.isNull());

        emit graphChanged();
        file.close();
        return true;
    }
    return false;
}

bool GraphScene::saveTo(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);

        // Save the nodes
        for (int row = 0; row < m_gridLayout->rowCount(); row++) {
            for (int column = 0; column < m_gridLayout->columnCount(); column++) {
                NodeItem *node = static_cast<NodeItem *>(m_gridLayout->itemAt(row, column));
                if (node) {
                    stream << "node " << node->name() << ' ' <<  node->nodeType() << ' '
                           << row << ' ' << column << endl;
                }
            }
        }

        // Save the edges
        foreach (const DirectedEdgeItem *edge, m_edges) {
            stream << "edge " << edge->name() << ' ' << edge->start()->name() << ' '
                   << edge->end()->name() << endl;
        }

        file.close();
        return true;
    }
    return false;
}

bool GraphScene::addEdge(NodeItem *start, NodeItem *end)
{
    if (start && end) {
        DirectedEdgeItem *edge = new DirectedEdgeItem(start, end, NULL, this);
        edge->setName(start->name() + end->name());
        return true;
    }
    return false;
}

void GraphScene::setInputNode(NodeItem *node)
{
    if (node) {
        if (m_inputNode) {
            m_inputNode->setNodeType(NodeItem::StandardNode);
        }
        node->setNodeType(NodeItem::InputNode);
    }
    m_inputNode = node;
    emit inputNodeChanged();
}

void GraphScene::setOuputNode(NodeItem *node)
{
    if (node) {
        if (m_outputNode) {
            m_outputNode->setNodeType(NodeItem::StandardNode);
        }
        node->setNodeType(NodeItem::OutputNode);
    }
    m_outputNode = node;
    emit outputNodeChanged();
}

int GraphScene::columnCount() const
{
    return m_gridLayout->rowCount();
}

int GraphScene::rowCount() const
{
    return m_gridLayout->columnCount();
}

NodeItem *GraphScene::selectedNode() const
{
    const QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size() == 1) {
        return qgraphicsitem_cast<NodeItem *>(selection.first());
    } else {
        return NULL;
    }
}

DirectedEdgeItem *GraphScene::selectedEdge() const
{
    const QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size() == 1) {
        return qgraphicsitem_cast<DirectedEdgeItem *>(selection.first());
    } else {
        return NULL;
    }
}

void GraphScene::init(InitType initType)
{
    // Remove all items from the scene
    foreach (QGraphicsItem *item, items()) {
        removeItem(item);
    }
    m_edges.clear();
    setInputNode(NULL);
    setOuputNode(NULL);

    // Set up layout-related stuff
    m_gridLayout = new QGraphicsGridLayout;
    m_gridLayout->setHorizontalSpacing(NODEITEM_PIXEL_DISTANCE);
    m_gridLayout->setVerticalSpacing(NODEITEM_PIXEL_DISTANCE);
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(m_gridLayout);
    addItem(form);

    if (initType == StandardInit) {
        // Create default input/output nodes and wire them
        NodeItem *n1 = new NodeItem(NULL, this);
        n1->setName("1");
        m_gridLayout->addItem(n1, 0, 0);
        NodeItem *n2 = new NodeItem(NULL, this);
        n2->setName("2");
        m_gridLayout->addItem(n2, 0, 1);
        DirectedEdgeItem *e12 = new DirectedEdgeItem(n1, n2, NULL, this);
        e12->setName("12");
        m_edges.append(e12);

        setInputNode(n1);
        setOuputNode(n2);
    }
    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::addRow()
{
    const int lastRow = m_gridLayout->rowCount();
    if (lastRow == 0) {
        m_gridLayout->addItem(new NodeItem(NULL, this), 0, 0);
    } else {
        for (int row = 0; row < m_gridLayout->columnCount(); row++) {
            m_gridLayout->addItem(new NodeItem(NULL, this), lastRow, row);
        }
    }
    updateNodeItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeRow()
{
    const int lastRow = m_gridLayout->rowCount() - 1;
    for (int row = 0; row < m_gridLayout->columnCount(); row++) {
        removeItem(dynamic_cast<QGraphicsItem *>(m_gridLayout->itemAt(lastRow, row)));
    }
    updateNodeItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::addColumn()
{
    const int lastColumn = m_gridLayout->columnCount();
    if (lastColumn == 0) {
        m_gridLayout->addItem(new NodeItem(NULL, this), 0, 0);
    } else {
        for (int column = 0; column < m_gridLayout->rowCount(); column++) {
            m_gridLayout->addItem(new NodeItem(NULL, this), column, lastColumn);
        }
    }
    updateNodeItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeColumn()
{
    const int lastColumn = m_gridLayout->columnCount() - 1;
    for (int column = 0; column < m_gridLayout->rowCount(); column++) {
        removeItem(dynamic_cast<QGraphicsItem *>(m_gridLayout->itemAt(column, lastColumn)));
    }
    updateNodeItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeSelectedItem()
{
    foreach (QGraphicsItem *item, selectedItems()) {
        removeItem(item);
    }
    updateNodeItemNames();
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Update arrow if we're currently dragging
    if (m_inDrag) {
        m_dragArrow->setLine(QLineF(m_dragArrow->line().p1(), event->scenePos()));
        clearSelection();   // We're draggin, unselect everything
    }
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Start a new edge drag if we pressed the left mouse button over a NodeItem
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos());
        if ((m_dragStartNode = qgraphicsitem_cast<NodeItem *>(item))) {
            m_dragArrow = new ArrowItem(QLineF(event->scenePos(), event->scenePos() + QPointF(1, 0)), NULL, this);
            m_dragArrow->setFlag(QGraphicsItem::ItemIsSelectable, false);
            m_inDrag = true;
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Create a new edge when releasing mouse over an NodeItem while dragging
    if (m_inDrag) {
        QGraphicsItem *item = itemAt(event->scenePos());
        NodeItem* dragEndNode;
        if ((dragEndNode = qgraphicsitem_cast<NodeItem *>(item))) {
            DirectedEdgeItem *edge = new DirectedEdgeItem(m_dragStartNode, dragEndNode, NULL, this);
            edge->setName(m_dragStartNode->name() + dragEndNode->name());
            m_edges.append(edge);
            m_dragStartNode = NULL;
        }
        delete m_dragArrow;
        m_dragArrow = NULL;
        m_inDrag = false;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphScene::removeItem(QGraphicsItem *item)
{
    const NodeItem *node = qgraphicsitem_cast<NodeItem *>(item);
    if (node) {
        // Nodes should be handled with care
        if (node == m_inputNode) {
            setInputNode(NULL);
        } else if (node == m_outputNode) {
            setOuputNode(NULL);
        }

        // Check if that node is the start or end of an edge and remove those edges
        // NOTE: This might not be the fastest way but currently does the trick
        foreach (DirectedEdgeItem *edge, m_edges) {
            if (node == edge->start() || node == edge->end()) {
                m_edges.removeOne(edge);
                delete edge;
            }
        }
    }
    delete item;
}

void GraphScene::updateNodeItemNames()
{
    for (int row = 0; row < m_gridLayout->rowCount(); row++) {
        for (int column = 0; column < m_gridLayout->columnCount(); column++) {
            NodeItem *node = static_cast<NodeItem *>(m_gridLayout->itemAt(row, column));
            if (node) {
                node->setName(QString::number(row * m_gridLayout->columnCount() + column + 1));
            }
        }
    }
}

#include "graphscene.moc"
