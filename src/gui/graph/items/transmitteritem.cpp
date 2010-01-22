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

#include "transmitteritem.h"

#include <QGraphicsScene>
#include <QPainter>

TransmitterItem::TransmitterItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : GraphItem(parent, scene), m_nameRect(-40, -10, 20, 20)
{
    setRect(-15, -70, 30, 140);
    setName("u(t)");

    m_lines << QLineF(15, -55, 25, -55) << QLineF(15, 55, 25, 55)
            << QLineF(-25, -55, -15, -55) << QLineF(-25, 55, -15, 55);
    m_dotRects << QRectF(-30, -57, 4, 4) << QRectF(-30, 53, 4, 4);
}

QRectF TransmitterItem::boundingRect() const
{
    QRectF rectLinesAndDots = QRectF(-31, -71, 62, 142);
    return rectLinesAndDots.united(m_nameRect);
}

QPainterPath TransmitterItem::shape() const
{
    QPainterPath path = QGraphicsRectItem::shape();
    path.addRect(m_nameRect);
    foreach (QLineF line, m_lines) {
        path.moveTo(line.p1());
        path.lineTo(line.p2());
    }
    foreach (QRectF dotRect, m_dotRects) {
        path.addRect(dotRect);
    }
    return path;
}

QPointF TransmitterItem::inputPos() const
{
    return QPointF(25, -55) + pos();
}

QPointF TransmitterItem::outputPos() const
{
    return QPointF(25, 55) + pos();
}

void TransmitterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = pen();
    QBrush b = brush();
    if (isSelected()) {
        p.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);
    painter->drawRect(rect());

    painter->drawLines(m_lines);
    foreach (QRectF dotRect, m_dotRects) {
        painter->drawEllipse(dotRect);
    }

    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(rect(), Qt::AlignCenter, "F");
    painter->drawText(m_nameRect, Qt::AlignCenter, m_name);
}