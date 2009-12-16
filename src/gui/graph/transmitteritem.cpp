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

#include "transmitteritem.h"

#include <QGraphicsScene>
#include <QPainter>

TransmitterItem::TransmitterItem(const QString &name, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent, scene)
    , m_name(name)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setRect(-15, -50, 30, 100);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(QColor(0, 0, 255, 10));

    m_lines << QLineF(15, -40, 25, -40) << QLineF(15, 40, 25, 40)
            << QLineF(-25, -40, -15, -40) << QLineF(-25, 40, -15, 40);
    m_dotRects << QRectF(-30, -42, 4, 4) << QRectF(-30, 38, 4, 4);
}

TransmitterItem::~TransmitterItem()
{
    scene()->removeItem(this);
}

QRectF TransmitterItem::boundingRect() const
{
    QRectF rectLinesAndDots = QRectF(-31, -51, 62, 102);
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

void TransmitterItem::setName(const QString &name)
{
    m_name = name;
    update();
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
    m_nameRect = QRectF(-40, -10, 20, 20);
    painter->drawText(m_nameRect, Qt::AlignCenter, m_name);
}
