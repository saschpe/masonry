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
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QSettings>
#include <QTextStream>

#define NODEITEM_PIXEL_DISTANCE 50

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_inputNode(NULL), m_outputNode(NULL), m_columns(0), m_rows(0)
{
    setBackgroundBrush(Qt::white);

    init();
}

void GraphScene::loadFrom(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
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
    }
}

void GraphScene::saveTo(const QString &fileName)
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
    }
}

void GraphScene::setInputNode(NodeItem *node)
{
    node->setNodeType(NodeItem::InputNode);
    m_inputNode = node;
    emit inputNodeChanged();
}

void GraphScene::setOuputNode(NodeItem *node)
{
    node->setNodeType(NodeItem::OutputNode);
    m_outputNode = node;
    emit outputNodeChanged();
}

void GraphScene::init()
{
    // Remove all items from the scene
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
    m_nodes.clear();
    m_edges.clear();

    // Add one node to the scene
    NodeItem *n = new NodeItem(NULL, this);
    n->setName("1");
    m_nodes.append(n);
    m_columns = 1;
    m_rows = 1;

    // Set default input/output nodes
    setInputNode(n);
    setOuputNode(n);
    emit graphChanged();
}

void GraphScene::readSettings()
{
    QSettings settings;

    // Load graphics view stuff
    settings.beginGroup("view");
    settings.beginGroup("advanced");
    bool movable = settings.value("graphItemsMovable").toBool();
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
    // Add 'm_column' nodes to the last (new) row
    for (int i = 1; i <= m_columns; i++) {
        NodeItem *n = new NodeItem(NULL, this);
        n->setName(QString::number(m_columns * m_rows + i));
        n->setPos(NODEITEM_PIXEL_DISTANCE * (i - 1), NODEITEM_PIXEL_DISTANCE * m_rows);
        m_nodes.append(n);
    }
    m_rows++;

    readSettings();
    setSceneRect(itemsBoundingRect());
    emit graphChanged();
}

void GraphScene::removeRow()
{
    // Remove 'm_columns' (all) nodes from the last row
    for (int i = 1; i <= m_columns; i++) {
        delete m_nodes.takeLast();
    }
    m_rows--;

    setSceneRect(itemsBoundingRect());
    emit graphChanged();
}

void GraphScene::addColumn()
{
    for (int i = 0; i < m_rows; i++) {
        NodeItem *n = new NodeItem(NULL, this);
        //n->setName(QString::number(m_columns * m_rows + i));
        n->setPos(NODEITEM_PIXEL_DISTANCE * m_columns, NODEITEM_PIXEL_DISTANCE * (i ));
        m_nodes.append(n);
    }
    m_columns++;

    for (int i = 0; i < m_nodes.size(); i++) {
        m_nodes[i]->setName(QString::number(i));
    }

    readSettings();
    setSceneRect(itemsBoundingRect());
    emit graphChanged();
}

void GraphScene::removeColumn()
{

    setSceneRect(itemsBoundingRect());
    emit graphChanged();
}

#include "graphscene.moc"
