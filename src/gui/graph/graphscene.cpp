/*
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
#include "arrowitem.h"
#include "directededgeitem.h"
#include "nodeitem.h"
#include "receiveritem.h"
#include "transmitteritem.h"

#include <QDebug>
#include <QList>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);

    //NOTE: This is test-only code that is going to be removed soon!
    NodeItem *node1 = new NodeItem;
    node1->setPos(100, 0);
    node1->setName("1");
    NodeItem *node2 = new NodeItem("2");
    node2->setPos(0, 10);
    node2->setName("2");
    NodeItem *node3 = new NodeItem("3");
    node3->setPos(-100, 50);
    node3->setRadius(20);
    DirectedEdgeItem *edge1 = new DirectedEdgeItem(node1, node2, "a");
    DirectedEdgeItem *edge2 = new DirectedEdgeItem(node2, node3, "b");

    addItem(node1);
    addItem(node2);
    addItem(node3);
    addItem(edge1);
    addItem(edge2);

    ArrowItem *arrow1 = new ArrowItem(0, -100, 100, -50, "a1");
    //arrow1->setPos(-100 0);
    addItem(arrow1);
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

/*void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}*/

#include "graphscene.moc"
