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

#include "directededgeitem.h"
#include "nodeitem.h"

#include <QGraphicsScene>

#include <cmath>
#ifdef Q_OS_WIN
// VC++-2008 does not recognise those (standard) constants
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif

DirectedEdgeItem::DirectedEdgeItem(NodeItem *startNodeItem, NodeItem *endNodeItem, const QString &name, QGraphicsItem *parent, QGraphicsScene *scene)
    : ArrowItem(QLineF(startNodeItem->pos(), endNodeItem->pos()), name, parent, scene)
    , m_startNodeItem(startNodeItem), m_endNodeItem(endNodeItem)
{
    m_startNodeItem->addEdgeItem(this);
    m_endNodeItem->addEdgeItem(this);
}

DirectedEdgeItem::~DirectedEdgeItem()
{
    m_startNodeItem->removeEdgeItem(this);
    m_endNodeItem->removeEdgeItem(this);
}

void DirectedEdgeItem::updatePosition()
{
    QLineF line(mapFromItem(m_startNodeItem, 0, 0), mapFromItem(m_endNodeItem, 0, 0));
    setLine(line);
}

void DirectedEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF l(m_startNodeItem->pos(), m_endNodeItem->pos());
    QPointF p1(m_startNodeItem->pos().x() + m_startNodeItem->radius() * sin(M_PI_2 + l.angle() / 180*M_PI),
               m_startNodeItem->pos().y() + m_startNodeItem->radius() * cos(M_PI_2 + l.angle() / 180*M_PI));
    QPointF p2(m_endNodeItem->pos().x() + m_endNodeItem->radius() * sin(l.angle() / 180*M_PI - M_PI_2),
               m_endNodeItem->pos().y() + m_endNodeItem->radius() * cos(l.angle() / 180*M_PI - M_PI_2));
    l.setP1(p1);
    l.setP2(p2);
    setLine(l);
    ArrowItem::paint(painter, option, widget);
}
