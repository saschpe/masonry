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
    , m_inputNode(NULL), m_outputNode(NULL)
{
    setBackgroundBrush(Qt::white);

    init();
}

bool GraphScene::loadFrom(const QString &fileName)
{
    QFile file(fileName);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QString tmp;                        // To read over strings used to structure the file
        int layerCount = 0;                 // Stores the layer count
        QTextStream stream(&file);

        init();                             // Reset the current graph
        //TODO: Load
        /*stream >> tmp >> layerCount;
        for (int i = 0; i < layerCount; i++) {
            int pos;
            stream >> tmp >> pos >> tmp;
            addLayer();                     // Add layers to the graph
            m_layers.last()->setName(tmp);  // Set the name of the layer
        }*/
        file.close();
        emit graphChanged();
        return true;
    }
    return false;
}

bool GraphScene::saveTo(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        //TODO: Save
        /*
        stream << "layer-count: " << m_layers.size() << endl;
        foreach (LayerItem *layer, m_layers) {
            stream << "layer-pos-name:" << layer->graphPos() << layer->name();
        }*/
        file.close();
        return true;
    }
    return false;
}

int GraphScene::columnCount() const
{
    return m_gridLayout->rowCount();
}

int GraphScene::rowCount() const
{
    return m_gridLayout->columnCount();
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

void GraphScene::init()
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
    }
    updateNodeItemNames();

    setSceneRect(m_gridLayout->geometry());
    emit graphChanged();
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
