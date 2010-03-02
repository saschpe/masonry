/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sasch.pe@gmx.de>

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

#include "graphscene.h"
#include "items/arrowitem.h"
#include "items/directededgeitem.h"
#include "items/nodeitem.h"

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
    , m_gridLayout(new QGraphicsGridLayout)
    , m_inDrag(false), m_dragArrow(NULL), m_dragStartNode(NULL)
    , m_inputNode(NULL), m_outputNode(NULL)
{
    setBackgroundBrush(Qt::white);

    m_gridLayout->setHorizontalSpacing(NODEITEM_PIXEL_DISTANCE); // Set up layout-related stuff
    m_gridLayout->setVerticalSpacing(NODEITEM_PIXEL_DISTANCE);
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(m_gridLayout);
    addItem(form);

    init(StandardInit);                                     // Init a standard scene
}

void GraphScene::init(InitType initType)
{
    // Remove all nodes from the scene (and thus also connecting edges)
    for (int row = 0; row < m_gridLayout->rowCount(); row++) {
        for (int column = 0; column < m_gridLayout->columnCount(); column++) {
            // If there is a node in that cell of the grid layout, remove it
            removeItem(static_cast<NodeItem *>(m_gridLayout->itemAt(row, column)));
        }
    }

    switch(initType) {                                      // Check how to init the scene
        case EmptyInit:
            setInputNode(NULL);                             // Reset input/output nodes
            setOuputNode(NULL);
            break;
        case StandardInit:
            NodeItem *n1 = new NodeItem(NULL, this);        // Create default input/output nodes
            n1->setName("1");
            m_gridLayout->addItem(n1, 0, 0);
            NodeItem *n2 = new NodeItem(NULL, this);
            n2->setName("2");
            m_gridLayout->addItem(n2, 0, 1);

            addEdge(n1, n2);                                // and wire them with an edge
            setInputNode(n1);                               // Set default input/output nodes
            setOuputNode(n2);
            break;
    }
    setSceneRect(QRectF());
    emit graphChanged();
}

bool GraphScene::loadFrom(const QString &fileName)
{
    QFile file(fileName);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QHash<QString, NodeItem *> nodes;                   // Temporary hashmap for faster lookup

        init(EmptyInit);                                    // Create an empty scene

        QString line;
        do {                                                // Iterate over all the lines in the file
            line = stream.readLine();                       // and split the line at ' ' characters
            const QStringList splittedLine = line.split(" ");
            if (splittedLine[0] == "node") {
                // Found a node, add it to the scene
                NodeItem *node = new NodeItem(NULL, this);
                node->setName(splittedLine[1]);
                NodeItem::NodeType nodeType = static_cast<NodeItem::NodeType>(splittedLine[2].toInt());
                switch (nodeType) {
                    case NodeItem::InputNode:
                        setInputNode(node);                 // We found the input node
                        break;
                    case NodeItem::OutputNode:
                        setOuputNode(node);                 // We found the ouput node
                        break;
                    case NodeItem::StandardNode:
                        // This should already be set by default but doesn't harm here
                        node->setNodeType(NodeItem::StandardNode);
                        break;
                }
                // There is obviously a (Matlab) formula attached, parse it...
                if (splittedLine.length() > 5) {
                    int formulaStart = line.indexOf('"');
                    QString formula = line;
                    formula.remove(0, formulaStart);
                    while (!formula.endsWith('"')) {        // Formula spans multiple lines
                        formula += '\n' + stream.readLine();
                    }
                    formula.chop(1);                        // Remove leading '"'
                    formula.remove(0, 1);                   // Remove trailing '"'
                    node->setFormula(formula);
                }

                nodes.insert(node->name(), node);
                m_gridLayout->addItem(node, splittedLine[3].toInt(), splittedLine[4].toInt());
            } else if (splittedLine[0] == "edge") {
                NodeItem *start = nodes[splittedLine[2]];   // Found an edge, add it to the scene
                NodeItem *end = nodes[splittedLine[3]];

                DirectedEdgeItem *edge = addEdge(start, end);
                edge->setName(splittedLine[1]);
                // There is obviously a (Matlab) formula attached, parse it...
                if (splittedLine.length() > 4) {
                    int formulaStart = line.indexOf('"');
                    QString formula = line;
                    formula.remove(0, formulaStart);
                    while (!formula.endsWith('"')) {        // Formula spans multiple lines
                        formula += '\n' + stream.readLine();
                    }
                    formula.chop(1);                        // Remove leading '"'
                    formula.remove(0, 1);                   // Remove trailing '"'
                    edge->setFormula(formula);
                }
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

        // Save the nodes with the following line format: 'node $NAME $TYPE $ROW $COL $FORMULA'
        for (int row = 0; row < m_gridLayout->rowCount(); row++) {
            for (int column = 0; column < m_gridLayout->columnCount(); column++) {
                NodeItem *node = static_cast<NodeItem *>(m_gridLayout->itemAt(row, column));
                if (node) {
                    stream << "node " << node->name() << ' ' << node->nodeType() << ' '
                           << row << ' ' << column << " \"" << node->formula() << '"' << endl;
                }
            }
        }
        // Save the edges with the following line format: 'edge $NAME $START $END $FORMULA'
        foreach (const DirectedEdgeItem *edge, m_edges) {
            stream << "edge " << edge->name() << ' ' << edge->start()->name() << ' '
                   << edge->end()->name() << " \"" << edge->formula() << '"' << endl;
        }
        file.close();
        return true;
    }
    return false;
}

DirectedEdgeItem *GraphScene::addEdge(NodeItem *start, NodeItem *end)
{
    if (start && end && start != end) {
        //qDebug() << "GraphScene::addEdge(" << start->name() << "," << end->name() << ")";
        DirectedEdgeItem *edge = new DirectedEdgeItem(start, end, NULL, this);
        edge->setName('s' + start->name() + end->name());
        m_edges.append(edge);
        return edge;
    }
    return NULL;
}

void GraphScene::setInputNode(NodeItem *node)
{
    if (m_inputNode) {
        m_inputNode->setNodeType(NodeItem::StandardNode);
    }
    if (node) {
        node->setNodeType(NodeItem::InputNode);
    }
    m_inputNode = node;
    emit inputNodeChanged();
}

void GraphScene::setOuputNode(NodeItem *node)
{
    if (m_outputNode) {
        m_outputNode->setNodeType(NodeItem::StandardNode);
    }
    if (node) {
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

void GraphScene::addRow()
{
    const int lastRow = m_gridLayout->rowCount();
    if (lastRow == 0) {                                     // Corner case, empty scene
        m_gridLayout->addItem(new NodeItem(NULL, this), 0, 0);
    } else {
        for (int row = 0; row < m_gridLayout->columnCount(); row++) {
            m_gridLayout->addItem(new NodeItem(NULL, this), lastRow, row);
        }
    }
    updateItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeRow()
{
    const int lastRow = m_gridLayout->rowCount() - 1;
    for (int row = 0; row < m_gridLayout->columnCount(); row++) {
        removeItem(dynamic_cast<QGraphicsItem *>(m_gridLayout->itemAt(lastRow, row)));
    }
    updateItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::addColumn()
{
    const int lastColumn = m_gridLayout->columnCount();
    if (lastColumn == 0) {                                  // Corner case, empty scene
        m_gridLayout->addItem(new NodeItem(NULL, this), 0, 0);
    } else {
        for (int column = 0; column < m_gridLayout->rowCount(); column++) {
            m_gridLayout->addItem(new NodeItem(NULL, this), column, lastColumn);
        }
    }
    updateItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeColumn()
{
    const int lastColumn = m_gridLayout->columnCount() - 1;
    for (int column = 0; column < m_gridLayout->rowCount(); column++) {
        removeItem(dynamic_cast<QGraphicsItem *>(m_gridLayout->itemAt(column, lastColumn)));
    }
    updateItemNames();

    setSceneRect(QRectF());
    emit graphChanged();
}

void GraphScene::removeSelectedItem()
{
    foreach (QGraphicsItem *item, selectedItems()) {
        removeItem(item);
    }
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
            addEdge(m_dragStartNode, dragEndNode);
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
    if (item) {
        const NodeItem *node = qgraphicsitem_cast<NodeItem *>(item);
        if (node) {
            if (node == m_inputNode) {                      // Nodes should be handled with care
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
        item = NULL;
    }
}

void GraphScene::updateItemNames()
{
    for (int row = 0; row < m_gridLayout->rowCount(); row++) {
        for (int column = 0; column < m_gridLayout->columnCount(); column++) {
            NodeItem *node = static_cast<NodeItem *>(m_gridLayout->itemAt(row, column));
            if (node) {
                node->setName(QString::number(column * m_gridLayout->columnCount() + row));
            }
        }
    }
}

#include "graphscene.moc"
