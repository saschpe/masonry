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
#include "nodeitem.h"
#include "receiveritem.h"
#include "transmitteritem.h"

#include <QDebug>
#include <QList>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
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
    int count = -1;
    //TODO: Implement
    return count;
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
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }

    TransmitterItem *tm = new TransmitterItem("u(t)", NULL, this);
    tm->setPos(-200, 0);
    ReceiverItem *rc = new ReceiverItem("s(t)", NULL, this);
    rc->setPos(200, 0);

    //NOTE: This is test-only code that is going to be removed soon!
    NodeItem *node1 = new NodeItem("1", NULL, this);
    node1->setPos(100, 0);
    NodeItem *node2 = new NodeItem("2", NULL, this);
    node2->setPos(0, 10);
    NodeItem *node3 = new NodeItem("3", NULL, this);
    node3->setPos(-100, 50);
    DirectedEdgeItem *edge1 = new DirectedEdgeItem(node1, node2, "12", NULL, this);
    DirectedEdgeItem *edge2 = new DirectedEdgeItem(node2, node3, "23", NULL, this);

    DirectedEdgeItem *tre1 = new DirectedEdgeItem(tm, node1, "t1", NULL, this);
    //DirectedEdgeItem *tre2 = new DirectedEdgeItem(node3, tm, "3t", NULL, this);

    ArrowItem *a1 = new ArrowItem(0, 0, 0, -50, "a1", NULL, this);

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
        item->setFlag(QGraphicsItem::ItemIsMovable, movable);
    }
    settings.endGroup();
    settings.endGroup();
}

void GraphScene::addLayer()
{
    emit graphChanged();
}

void GraphScene::removeLayer()
{
    emit graphChanged();
}

#include "graphscene.moc"
