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
#include "directededgeitem.h"
#include "layeritem.h"
#include "nodeitem.h"
#include "receiveritem.h"
#include "transmitteritem.h"

#include <QDebug>
#include <QList>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QSettings>

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);

    init();
}

void GraphScene::loadFrom(const QString &fileName)
{
    qDebug() << "GraphScene::loadFrom()" << "TODO: implement!";
    emit graphChanged();
}

void GraphScene::saveTo(const QString &fileName)
{
    qDebug() << "GraphScene::saveTo()" << "TODO: implement!";
}

int GraphScene::layerCount() const
{
    return m_layers.size();
}

int GraphScene::nodeCount() const
{
    int count = 0;
    foreach (QGraphicsItem *item, items()) {
        if (dynamic_cast<NodeItem *>(item) != 0) {
            count++;
        }
    }
    return count;
}

int GraphScene::edgeCount() const
{
    int count = 0;
    foreach (QGraphicsItem *item, items()) {
        if (dynamic_cast<DirectedEdgeItem *>(item) != 0) {
            count ++;
        }
    }
    return count;
}

void GraphScene::init()
{
    // Erase all items from scene
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
    m_layers.clear();

    m_transmitter = new TransmitterItem("u(t)", NULL, this);
    m_transmitter->setPos(-100, 0);
    m_receiver = new ReceiverItem("s(t)", NULL, this);
    m_receiver->setPos(100, 0);

    new DirectedEdgeItem(m_transmitter, m_receiver, "tr", NULL, this);
    new DirectedEdgeItem(m_receiver, m_transmitter, "rt", NULL, this);

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
    m_receiver->removeEdgeItems();

    LayerItem *newLayer = new LayerItem("1", NULL, this);
    if (m_layers.size() > 0) {
        LayerItem *lastLayer = m_layers.last();

        newLayer->setPos(lastLayer->pos() + QPointF(100, 0));
        m_receiver->moveBy(100, 0);

        /*new DirectedEdgeItem(lastLayer->nodes()[2], newLayer->nodes()[0], "x", NULL, this);
        new DirectedEdgeItem(newLayer->nodes()[1], lastLayer->nodes()[3], "x", NULL, this);*/
    } else {
        newLayer->setPos(0, 0);

        //TODO: Connect first layer to transmitter
    }
    newLayer->adjustNamingTo(m_layers.size());
    m_layers.append(newLayer);

    // Connect new layer to receiver
    //new DirectedEdgeItem(newLayer->nodes()->at(2), m_receiver, "", NULL, this);
    //new DirectedEdgeItem(m_receiver, newLayer->nodes()->at(3), "", NULL, this);

    emit graphChanged();
}

void GraphScene::removeLayer()
{
    if (m_layers.size() == 0) {
        return;
    }

    m_receiver->removeEdgeItems();

    // Remove last layer from scene
    delete m_layers.takeLast();

    // Adjust receiver position to make it look good and all views
    if (m_layers.size() > 0) {
        m_receiver->moveBy(-100, 0);
    }

    //TODO: ...

    emit graphChanged();
}

#include "graphscene.moc"
