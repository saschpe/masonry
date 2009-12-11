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

#include "nodeitem.h"
#include "directededgeitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPen>
#include <QRadialGradient>

NodeItem::NodeItem(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsEllipseItem(parent, scene)
    , m_contextMenu(contextMenu)
{
    setRect(0, 0, 20, 20);

    QRadialGradient gradient(10, 10, 10);
    gradient.setColorAt(0, QColor::fromRgbF(1, 0.9, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(1, 0.7, 0, 1));
    QBrush fillBrush(gradient);
    setBrush(fillBrush);
    QPen pen;
    pen.setWidthF(0.3);
    setPen(pen);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void NodeItem::addEdgeItem(DirectedEdgeItem *item)
{
    m_edgeItems.append(item);
};

void NodeItem::removeEdgeItem(DirectedEdgeItem *item)
{
    int index = m_edgeItems.indexOf(item);
    if (index != -1 ) {
        m_edgeItems.removeAt(index);
    }
}

void NodeItem::removeEdgeItems()
{
    foreach (DirectedEdgeItem *edgeItem, m_edgeItems) {
        edgeItem->startNodeItem()->removeEdgeItem(edgeItem);
        edgeItem->endNodeItem()->removeEdgeItem(edgeItem);
        scene()->removeItem(edgeItem);
        delete edgeItem;
    }
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (DirectedEdgeItem *edgeItem, m_edgeItems) {
            edgeItem->updatePosition();
        }
    }
    return value;
}
