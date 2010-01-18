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
#define M_PI   3.14159265358979323846   // VC++-2008 does not recognise those (standard) constants
#define M_PI_2 1.57079632679489661923
#endif

DirectedEdgeItem::DirectedEdgeItem(GraphItem *startGraphItem, GraphItem *endGraphItem, const QString &name, QGraphicsItem *parent, QGraphicsScene *scene)
    : ArrowItem(QLineF(startGraphItem->inputPos(), endGraphItem->outputPos()), name, parent, scene)
    , m_startGraphItem(startGraphItem), m_endGraphItem(endGraphItem)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    m_startGraphItem->addEdgeItem(this);
    m_endGraphItem->addEdgeItem(this);
}

DirectedEdgeItem::~DirectedEdgeItem()
{
    m_startGraphItem->removeEdgeItem(this);
    m_endGraphItem->removeEdgeItem(this);
}

void DirectedEdgeItem::updatePosition()
{
    QLineF line(mapFromItem(m_startGraphItem, m_startGraphItem->inputPos()),
                mapFromItem(m_endGraphItem, m_endGraphItem->outputPos()));
    setLine(line);
}

void DirectedEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF l(m_startGraphItem->inputPos(), m_endGraphItem->outputPos());

     NodeItem *node;
    if ((node = dynamic_cast<NodeItem *>(m_startGraphItem)) != NULL) {
        QPointF p1(node->pos().x() + node->radius() * sin(M_PI_2 + l.angle() / 180*M_PI),
                   node->pos().y() + node->radius() * cos(M_PI_2 + l.angle() / 180*M_PI));
        l.setP1(p1);
    }
    if ((node = dynamic_cast<NodeItem *>(m_endGraphItem)) != NULL) {
        QPointF p2(node->pos().x() + node->radius() * sin(l.angle() / 180*M_PI - M_PI_2),
                   node->pos().y() + node->radius() * cos(l.angle() / 180*M_PI - M_PI_2));
        l.setP2(p2);
    }
    setLine(l);
    ArrowItem::paint(painter, option, widget);
}
