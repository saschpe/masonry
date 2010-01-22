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

#include "layeritem.h"
#include "directededgeitem.h"
#include "nodeitem.h"

#include <QGraphicsScene>
#include <QPainter>

LayerItem::LayerItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : GraphItem(parent, scene)
    , m_color(200, 0, 200, 10), m_graphPos(NULL), m_nameRect(-35, -90, 70, 20)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setRect(-35, -70, 70, 140);
    setPen(QPen(m_color, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(m_color);

    // Add internal layer nodes with default naming
    m_nodes.append(new NodeItem(this, scene));
    m_nodes.append(new NodeItem(this, scene));
    m_nodes.append(new NodeItem(this, scene));
    m_nodes.append(new NodeItem(this, scene));
    m_nodes[0]->setPos(-20, -55);
    m_nodes[1]->setPos(-20, 55);
    m_nodes[2]->setPos(20, -55);
    m_nodes[3]->setPos(20, 55);

    // Wire the internal nodes
    m_edges.append(new DirectedEdgeItem(m_nodes[0], m_nodes[2], this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[2], m_nodes[3], this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[3], m_nodes[1], this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[1], m_nodes[0], this, scene));

    adjustNamingTo(m_graphPos);
}

void LayerItem::adjustNamingTo(int pos)
{
    int off = 4 * pos;
    m_graphPos = pos;

    m_nodes[0]->setName(QString::number(off + 1));
    m_nodes[1]->setName(QString::number(off + 2));
    m_nodes[2]->setName(QString::number(off + 3));
    m_nodes[3]->setName(QString::number(off + 4));

    m_edges[0]->setName("tg" + QString::number(pos + 1));
    m_edges[1]->setName("-g" + QString::number(pos + 1));
    m_edges[2]->setName("tg" + QString::number(pos + 1));
    m_edges[3]->setName("g" + QString::number(pos + 1));
}

QRectF LayerItem::boundingRect() const
{
    return rect().united(m_nameRect);
}

QPainterPath LayerItem::shape() const
{
    QPainterPath path = QGraphicsRectItem::shape();
    path.addRect(m_nameRect);
    return path;
}

void LayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = pen();
    QBrush b = brush();
    /*if (isSelected()) {
        p.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);*/
    //painter->drawRect(rect());

    GraphItem::paint(painter, option, widget);

    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(rect(), Qt::AlignCenter, m_name);
    painter->drawText(m_nameRect, Qt::AlignCenter, m_name);
}

