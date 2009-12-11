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

#include "directededgeitem.h"
#include "nodeitem.h"
#include <cmath>

#include <QPainter>
#include <QPen>

const qreal Pi = 3.14;

DirectedEdgeItem::DirectedEdgeItem(NodeItem *startNodeItem, NodeItem *endNodeItem, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
    , m_startNodeItem(startNodeItem), m_endNodeItem(endNodeItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_startNodeItem->addEdgeItem(this);
    m_endNodeItem->addEdgeItem(this);
}

QRectF DirectedEdgeItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
              .normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath DirectedEdgeItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_arrowHead);
    return path;
}

void DirectedEdgeItem::updatePosition()
{
    QLineF line(mapFromItem(m_startNodeItem, 0, 0), mapFromItem(m_endNodeItem, 0, 0));
    setLine(line);
}

void DirectedEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_startNodeItem->collidesWithItem(m_endNodeItem)) {
        return;
    }

    QLineF centerLine(m_startNodeItem->pos(), m_endNodeItem->pos());
    /*QPolygonF endPolygon = m_endNodeItem->polygon();
    QPointF p1 = endPolygon.first() + m_endNodeItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); i++) {
        p2 = endPolygon.at(i) + m_endNodeItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection) {
            break;
        }
        p1 = p2;
    }*/
    /*QPointF endNodeItemCenter = m_endNodeItem->rect()->center();
    qreal endNodeItemRadius = m_endNodeItem->rect()->width() / 2;*/

    //setLine(QLineF(intersectPoint, m_startNodeItem->pos()));
    setLine(centerLine);

    QPen p = pen();
    QBrush b(Qt::black);
    if (isSelected()) {
        p.setColor(Qt::red);
        b.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0) {
        angle = (Pi * 2) - angle;
    }

    qreal arrowSize = 5;
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);
    m_arrowHead.clear();
    m_arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(m_arrowHead);
}
