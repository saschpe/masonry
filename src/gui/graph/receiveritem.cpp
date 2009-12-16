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

#include "receiveritem.h"

#include <QGraphicsScene>
#include <QPainter>

ReceiverItem::ReceiverItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent, scene)
{
}

ReceiverItem::~ReceiverItem()
{
    scene()->removeItem(this);
}

QRectF ReceiverItem::boundingRect() const
{
    QRectF boundingRect = rect();
    return boundingRect;
}

QPainterPath ReceiverItem::shape() const
{
    QPainterPath path = QGraphicsRectItem::shape();
    //TODO: Add something
    return path;
}

void ReceiverItem::setName(const QString &name)
{
    m_name = name;
    update();
}

void ReceiverItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = pen();
    QBrush b(Qt::black);
    if (isSelected()) {
        p.setColor(Qt::red);
        b.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);

    painter->drawRect(rect());

    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(rect(), Qt::AlignCenter, m_name);
}
