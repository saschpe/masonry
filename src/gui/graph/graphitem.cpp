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

#include "graphitem.h"
#include "directededgeitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

GraphItem::GraphItem(const QString &name, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent, scene)
    , m_contextMenu(0), m_name(name)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(QColor(0, 0, 255, 10));
}

GraphItem::~GraphItem()
{
    foreach (DirectedEdgeItem *edgeItem, m_edgeItems) {
        delete edgeItem;
    }
    scene()->removeItem(this);
}

void GraphItem::setContextMenu(QMenu *contextMenu)
{
    m_contextMenu = contextMenu;
}

void GraphItem::addEdgeItem(DirectedEdgeItem *item)
{
    m_edgeItems.append(item);
};

void GraphItem::removeEdgeItem(DirectedEdgeItem *item)
{
    int index = m_edgeItems.indexOf(item);
    if (index != -1 ) {
        m_edgeItems.removeAt(index);
    }
}

void GraphItem::setName(const QString &name)
{
    m_name = name;
    update();
}

QPointF GraphItem::inputPos() const
{
    return pos();
}

QPointF GraphItem::outputPos() const
{
    return pos();
}

void GraphItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_contextMenu) {
        return;
    }
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant GraphItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (DirectedEdgeItem *edgeItem, m_edgeItems) {
            edgeItem->updatePosition();
        }
    }
    return value;
}
