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

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

DirectedEdgeItem::DirectedEdgeItem(NodeItem *startNodeItem, NodeItem *endNodeItem, const QString &name, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
    , m_startNodeItem(startNodeItem), m_endNodeItem(endNodeItem), m_name(name)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_startNodeItem->addEdgeItem(this);
    m_endNodeItem->addEdgeItem(this);
}

DirectedEdgeItem::~DirectedEdgeItem()
{
    m_startNodeItem->removeEdgeItem(this);
    m_endNodeItem->removeEdgeItem(this);
    scene()->removeItem(this);
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
    path.addRect(m_textRect);
    return path;
}

void DirectedEdgeItem::setName(const QString &name)
{
    m_name = name;
    update();
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

    QLineF l(m_startNodeItem->pos(), m_endNodeItem->pos());
    QPointF p1(m_startNodeItem->pos().x() + m_startNodeItem->radius() * sin(M_PI_2 + l.angle() / 180*M_PI),
               m_startNodeItem->pos().y() + m_startNodeItem->radius() * cos(M_PI_2 + l.angle() / 180*M_PI));
    QPointF p2(m_endNodeItem->pos().x() + m_endNodeItem->radius() * sin(l.angle() / 180*M_PI - M_PI_2),
               m_endNodeItem->pos().y() + m_endNodeItem->radius() * cos(l.angle() / 180*M_PI - M_PI_2));
    l.setP1(p1);
    l.setP2(p2);
    setLine(l);

    QPen p = pen();
    QBrush b(Qt::black);
    if (isSelected()) {
        p.setColor(Qt::red);
        b.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);

    double arrowAngle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0) {
        arrowAngle = (M_PI * 2) - arrowAngle;
    }
    qreal arrowSize = 7;
    QPointF arrowP1 = line().p1() + QPointF(sin(arrowAngle + M_PI / 3) * arrowSize,
                                            cos(arrowAngle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(arrowAngle + M_PI - M_PI / 3) * arrowSize,
                                            cos(arrowAngle + M_PI - M_PI / 3) * arrowSize);
    m_arrowHead.clear();
    m_arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(m_arrowHead);

    // Make sure that the 'name' text is correctly aligned besides the line
    QPointF middle = l.pointAt(0.5);
    m_textRect = QRectF(middle.x() - 10, middle.y() - 10, 20, 20);
    qreal angle = l.angle();
    if (line().dy() >= 0) {
        m_textRect.translate(0, 10);
    } else {
        m_textRect.translate(0, -10);
    }
    if (angle > 30 && angle <= 90 || angle >= 270 && angle < 330) {
        m_textRect.translate(-10, 0);
    }
    if (angle > 90 && angle < 150 || angle > 210 && angle < 270) {
        m_textRect.translate(10, 0);
    }

    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(m_textRect, Qt::AlignCenter, m_name);
}
