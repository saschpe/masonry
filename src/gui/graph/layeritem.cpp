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

LayerItem::LayerItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent, scene)
    , m_color(200, 0, 200, 10)
{
    setRect(-30, -60, 60, 120);
    setPen(QPen(m_color, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(m_color);

    // Add internal layer nodes with default naming
    m_nodes.append(new NodeItem("1", this, scene));
    m_nodes.append(new NodeItem("2", this, scene));
    m_nodes.append(new NodeItem("3", this, scene));
    m_nodes.append(new NodeItem("4", this, scene));
    m_nodes[0]->setPos(-15, -40);
    m_nodes[1]->setPos(-15, 40);
    m_nodes[2]->setPos(15, -40);
    m_nodes[3]->setPos(15, 40);

    // Wire the internal nodes
    m_edges.append(new DirectedEdgeItem(m_nodes[0], m_nodes[2], "", this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[2], m_nodes[3], "", this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[3], m_nodes[1], "", this, scene));
    m_edges.append(new DirectedEdgeItem(m_nodes[1], m_nodes[0], "", this, scene));
}

LayerItem::~LayerItem()
{
    foreach (NodeItem *node, m_nodes) {
        delete node;
    }
    scene()->removeItem(this);
}

void LayerItem::adjustNamingTo(int pos)
{
    int off = 4 * pos;
    m_nodes[0]->setName(QString::number(off + 1));
    m_nodes[1]->setName(QString::number(off + 2));
    m_nodes[2]->setName(QString::number(off + 3));
    m_nodes[3]->setName(QString::number(off + 4));
    /*m_edges[0]->setName(QString::number(off + 1) + QString::number(off + 3));
    m_edges[1]->setName(QString::number(off + 3) + QString::number(off + 4));
    m_edges[2]->setName(QString::number(off + 4) + QString::number(off + 2));
    m_edges[3]->setName(QString::number(off + 2) + QString::number(off + 1));*/
}
