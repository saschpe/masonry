/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sasch.pe@gmx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "directededgeitem.h"
#include "nodeitem.h"

#include <QGraphicsScene>

#include <cmath>
#ifdef Q_OS_WIN
#define M_PI   3.14159265358979323846   // VC++-2008 does not recognise those (standard) constants
#define M_PI_2 1.57079632679489661923
#endif

DirectedEdgeItem::DirectedEdgeItem(GraphItem *start, GraphItem *end, QGraphicsItem *parent, QGraphicsScene *scene)
    : ArrowItem(QLineF(start->inputPos(), end->outputPos()), parent, scene)
    , m_start(start), m_end(end)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

void DirectedEdgeItem::setStart(GraphItem *start)
{
    m_start = start;
    update();
}

void DirectedEdgeItem::setEnd(GraphItem *end)
{
    m_end = end;
    update();
}

void DirectedEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF l(m_start->inputPos(), m_end->outputPos());

    NodeItem *node;
    if ((node = qgraphicsitem_cast<NodeItem *>(m_start)) != NULL) {
        QPointF p1(node->pos().x() + node->radius() * sin(M_PI_2 + l.angle() / 180*M_PI),
                   node->pos().y() + node->radius() * cos(M_PI_2 + l.angle() / 180*M_PI));
        l.setP1(p1);
    }
    if ((node = qgraphicsitem_cast<NodeItem *>(m_end)) != NULL) {
        QPointF p2(node->pos().x() + node->radius() * sin(l.angle() / 180*M_PI - M_PI_2),
                   node->pos().y() + node->radius() * cos(l.angle() / 180*M_PI - M_PI_2));
        l.setP2(p2);
    }
    setLine(l);
    ArrowItem::paint(painter, option, widget);
}
