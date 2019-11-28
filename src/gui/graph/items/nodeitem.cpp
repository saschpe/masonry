/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sascha@peilicke.de>

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

#include "nodeitem.h"

#include <QGraphicsScene>
#include <QPainter>

NodeItem::NodeItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : GraphItem(parent, scene)
    , m_nodeType(StandardNode), m_radius(10)
{
    setRect(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
    setBrush(Qt::white);
    setZValue(42);  // Just something higher than the default, NodeItems should be above everything else
}

void NodeItem::setGeometry(const QRectF &rect)
{
    setPos(rect.center());
    setRadius(rect.width() / 2);
}

void NodeItem::setRadius(qreal radius)
{
    m_radius = radius;
    setRect(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
    update();
}

void NodeItem::setNodeType(NodeType nodeType)
{
    m_nodeType = nodeType;
    switch (m_nodeType) {
        case InputNode:
            setBrush(Qt::green);
            break;
        case OutputNode:
            setBrush(Qt::cyan);
            break;
        case StandardNode:
            setBrush(Qt::white);
            break;
    }
    update();
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = pen();
    QBrush b = brush();
    if (isSelected()) {
        p.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);
    painter->drawEllipse(rect());
    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(rect(), Qt::AlignCenter, m_name);
}

QSizeF NodeItem::sizeHint(Qt::SizeHint which, const QSizeF &constraints) const
{
    return rect().size();
}
