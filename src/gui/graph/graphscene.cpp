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
    foreach (QGraphicsItem *item, items()) {
        DirectedEdgeItem *edge;
        if ((edge = dynamic_cast<DirectedEdgeItem *>(item)) != 0) {
            edges.append(edge);
        }
    }
    return edges;
}

QList<NodeItem *> GraphScene::nodes() const
{
    QList<NodeItem *> nodes;
    foreach (QGraphicsItem *item, items()) {
        NodeItem *node;
        if ((node = dynamic_cast<NodeItem *>(item)) != 0) {
            nodes.append(node);
        }
    }
    return nodes;
}

void GraphScene::init()
{
    // Erase all items from scene
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
    m_layers.clear();

    m_transmitter = new TransmitterItem(NULL, this);
    m_transmitter->setPos(-100, 0);
    m_receiver = new ReceiverItem(NULL, this);
    m_receiver->setPos(100, 0);

    m_receiverEdges.append(new DirectedEdgeItem(m_transmitter, m_receiver, NULL, this));
    m_receiverEdges.append(new DirectedEdgeItem(m_receiver, m_transmitter, NULL, this));

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
        // Everything except DirectedEdgeItem instances are movable.
        if (dynamic_cast<DirectedEdgeItem *>(item) == NULL) {
            item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        }
    }
    settings.endGroup();
    settings.endGroup();
}

void GraphScene::addLayer()
{
    foreach (DirectedEdgeItem *receiverEdge, m_receiverEdges) {
        delete receiverEdge;
    }

    LayerItem *last = new LayerItem(NULL, this);
    if (m_layers.size() > 0) {
        LayerItem *previous = m_layers.last();

        // Connect new last layer with previous last layer
        new DirectedEdgeItem(previous->nodes()->at(2), last->nodes()->at(0), NULL, this);
        new DirectedEdgeItem(last->nodes()->at(1), previous->nodes()->at(3), NULL, this);

        last->setPos(previous->pos() + QPointF(100, 0));
        last->update();
        m_receiver->moveBy(100, 0);
        m_receiver->update();
    } else {
        // Connect first layer with transmitter
        new DirectedEdgeItem(m_transmitter, last->nodes()->at(0), NULL, this);
        new DirectedEdgeItem(last->nodes()->at(1), m_transmitter, NULL, this);

        last->setPos(0, 0);
        last->update();
    }
    last->adjustNamingTo(m_layers.size());
    last->setName("Layer " + QString::number(m_layers.size()));
    m_layers.append(last);

    // Connect new layer to receiver
    m_receiverEdges.append(new DirectedEdgeItem(last->nodes()->at(2), m_receiver, NULL, this));
    m_receiverEdges.append(new DirectedEdgeItem(m_receiver, last->nodes()->at(3), NULL, this));

    readSettings();
    emit graphChanged();
}

void GraphScene::removeLayer()
{
    if (m_layers.size() == 0) {
        return;
    }

    foreach (DirectedEdgeItem *receiverEdge, m_receiverEdges) {
        delete receiverEdge;
    }

    // Remove last layer from scene
    delete m_layers.takeLast();

    // Adjust receiver position to make it look good and all views
    if (m_layers.size() > 0) {
        m_receiver->moveBy(-100, 0);
        LayerItem *previous = m_layers.last();

        // Connect new last layer to receiver
        m_receiverEdges.append(new DirectedEdgeItem(previous->nodes()->at(2), m_receiver, NULL, this));
        m_receiverEdges.append(new DirectedEdgeItem(m_receiver, previous->nodes()->at(3), NULL, this));
    } else {
        // Re-connect transmitter and receiver when no layers are left
        m_receiverEdges.append(new DirectedEdgeItem(m_transmitter, m_receiver, NULL, this));
        m_receiverEdges.append(new DirectedEdgeItem(m_receiver, m_transmitter, NULL, this));
    }

    emit graphChanged();
}

#include "graphscene.moc"
