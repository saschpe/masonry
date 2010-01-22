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
#include "items/layeritem.h"
#include "items/nodeitem.h"
#include "items/receiveritem.h"
#include "items/transmitteritem.h"

#include <QFile>
#include <QList>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QSettings>
#include <QTextStream>

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
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
        stream >> tmp >> layerCount;
        for (int i = 0; i < layerCount; i++) {
            int pos;
            stream >> tmp >> pos >> tmp;
            addLayer();                     // Add layers to the graph
            m_layers.last()->setName(tmp);  // Set the name of the layer
        }
        file.close();
    }

    emit graphChanged();
}

void GraphScene::saveTo(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        stream << "layer-count: " << m_layers.size() << endl;
        foreach (LayerItem *layer, m_layers) {
            stream << "layer-pos-name:" << layer->graphPos() << layer->name();
        }
        file.close();
    }
}

QList<DirectedEdgeItem *> GraphScene::edges() const
{
    QList<DirectedEdgeItem *> edges;
    edges.append(m_transmitterEdge);
    edges.append(m_layerEdges);
    foreach (LayerItem *layer, m_layers) {
        edges.append(layer->edges());
    }
    edges.append(m_receiverEdge);
    return edges;
}

QList<NodeItem *> GraphScene::nodes() const
{
    QList<NodeItem *> nodes;
    foreach (LayerItem *layer, m_layers) {
        nodes.append(*layer->nodes());
    }
    return nodes;
}

void GraphScene::init()
{
    // Erase all items from scene
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
    m_layerEdges.clear();
    m_layers.clear();

    // Create receiver and transmitter items and position them in the scene
    m_transmitter = new TransmitterItem(NULL, this);
    m_transmitter->setPos(-100, 0);
    m_receiver = new ReceiverItem(NULL, this);
    m_receiver->setPos(100, 0);

    // Connect receiver and transmitter
    m_transmitterEdge = new DirectedEdgeItem(m_transmitter, m_receiver, NULL, this);
    m_receiverEdge = new DirectedEdgeItem(m_receiver, m_transmitter, NULL, this);

    readSettings();
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
        // Everything except DirectedEdgeItems and LayerItems is movable.
        if (dynamic_cast<DirectedEdgeItem *>(item) == NULL &&
            dynamic_cast<LayerItem *>(item) == NULL) {
            item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        }
    }
    settings.endGroup();
    settings.endGroup();
}

void GraphScene::addLayer()
{
    LayerItem *last = new LayerItem(NULL, this);

    // Connect layer with receiver
    m_layerEdges.append(new DirectedEdgeItem(last->nodes()->at(2), m_receiver, NULL, this));
    m_receiverEdge->setEnd(last->nodes()->at(3));

    if (m_layers.size() == 0) {
        // Connect layer with transmitter
        m_layerEdges.append(new DirectedEdgeItem(last->nodes()->at(1), m_transmitter, NULL, this));
        m_transmitterEdge->setEnd(last->nodes()->at(0));

        last->setPos(0, 0);
    } else {
        LayerItem *previous = m_layers.last();

        // Connect layer with previous layer
        m_layerEdges.last()->setEnd(last->nodes()->at(0));
        m_layerEdges.append(new DirectedEdgeItem(last->nodes()->at(1), previous->nodes()->at(3), NULL, this));

        last->setPos(previous->pos() + QPointF(100, 0));
        m_receiver->moveBy(100, 0);
    }
    last->adjustNamingTo(m_layers.size());
    last->setName("Layer " + QString::number(m_layers.size()));
    m_layers.append(last);

    readSettings();
    emit graphChanged();
}

void GraphScene::removeLayer()
{
    if (m_layers.size() == 0) {
        return;
    }

    // Remove last layer and it's edges from scene
    delete m_layerEdges.takeLast();
    delete m_layerEdges.takeLast();
    delete m_layers.takeLast();

    // Adjust receiver position to make it look good and all views
    if (m_layers.size() == 0) {
        // Connect transmitter and receiver when no layers are left
        m_receiverEdge->setEnd(m_transmitter);
        m_transmitterEdge->setEnd(m_receiver);
    } else if (m_layers.size() == 1) {
        // Connect layer to receiver
        m_layerEdges.last()->setEnd(m_receiver);
        m_receiverEdge->setEnd(m_layers.last()->nodes()->at(3));

        // Connect layer to transmitter
        m_layerEdges.first()->setEnd(m_transmitter);
        m_transmitterEdge->setEnd(m_layers.last()->nodes()->at(1));

        m_receiver->moveBy(-100, 0);
    } else {
        // Connect layer with receiver
        m_layerEdges.last()->setEnd(m_receiver);
        m_receiverEdge->setEnd(m_layers.last()->nodes()->at(3));

        m_receiver->moveBy(-100, 0);
    }

    emit graphChanged();
}

#include "graphscene.moc"
