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
        foreach (DirectedEdgeItem *edge, m_edges) {
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
        m_inputNode = node;
        emit inputNodeChanged();
    }
}

void GraphScene::setOuputNode(NodeItem *node)
{
    if (node) {
        if (m_outputNode) {
            m_outputNode->setNodeType(NodeItem::StandardNode);
        }
        node->setNodeType(NodeItem::OutputNode);
        m_outputNode = node;
        emit outputNodeChanged();
    }
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
    QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size() == 1) {
        return dynamic_cast<NodeItem *>(selection.first());
    } else {
        return NULL;
    }
}

void GraphScene::init(InitType initType)
{
    // Remove all items from the scene
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
    m_edges.clear();
    m_inputNode = NULL;
    m_outputNode = NULL;

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
    emit graphChanged();
}

void GraphScene::readSettings()
{
    QSettings settings;

    // Load graphics view stuff
    settings.beginGroup("view");
    settings.beginGroup("advanced");
    const bool movable = settings.value("graphItemsMovable").toBool();
    foreach (QGraphicsItem *item, items()) {
        // Only nodes are movable
        if (dynamic_cast<NodeItem *>(item)) {
            item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        }
    }
    settings.endGroup();
    settings.endGroup();
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

    readSettings();
    setSceneRect(m_gridLayout->geometry());
    emit graphChanged();
}

void GraphScene::removeRow()
{
    const int lastRow = m_gridLayout->rowCount() - 1;
    for (int row = 0; row < m_gridLayout->columnCount(); row++) {
        delete m_gridLayout->itemAt(lastRow, row);
        //TODO: Set to NULL
    }
    updateNodeItemNames();

    setSceneRect(m_gridLayout->geometry());
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

    readSettings();
    setSceneRect(m_gridLayout->geometry());
    emit graphChanged();
}

void GraphScene::removeColumn()
{
    const int lastColumn = m_gridLayout->columnCount() - 1;
    for (int column = 0; column < m_gridLayout->rowCount(); column++) {
        delete m_gridLayout->itemAt(column, lastColumn);
        //TODO: Set to NULL
    }
    updateNodeItemNames();

    setSceneRect(m_gridLayout->geometry());
    emit graphChanged();
}

bool GraphScene::removeSelectedNode()
{
    QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size() == 1) {
        //TODO: Add a check if this is a NodeItem
        NodeItem *node = dynamic_cast<NodeItem *>(selection.first());
        //TODO: Set to NULL
        delete node;
        return true;
    } else {
        return false;
    }
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Update arrow if where currently dragging
    if (m_inDrag) {
        m_dragArrow->setLine(QLineF(m_dragArrow->line().p1(), event->scenePos()));
    }
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Start a new edge drag if we pressed the left mouse button over a NodeItem
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos());
        if ((m_dragStartNode = qgraphicsitem_cast<NodeItem *>(item))) {
            m_dragArrow = new ArrowItem(QLineF(event->scenePos(), event->scenePos()), NULL, this);
            m_dragArrow->setPen(QPen(Qt::lightGray));
            addItem(m_dragArrow);
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
        removeItem(m_dragArrow);
        delete m_dragArrow;
        m_dragArrow = NULL;
        m_inDrag = false;
    }
    QGraphicsScene::mouseReleaseEvent(event);
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
