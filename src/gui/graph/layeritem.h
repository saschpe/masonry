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

#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QGraphicsRectItem>

class DirectedEdgeItem;
class NodeItem;

class LayerItem : public QGraphicsRectItem
{
public:
    enum {Type = UserType + 104};

    LayerItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    //LayerItem(GraphItem *startGraphItem, GraphItem *endGraphItem, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~LayerItem();

    void setColor(QColor color);
    QColor color() const { return m_color; }

    QList<NodeItem *> nodes() const { return m_nodes; }
    void adjustNamingTo(int pos);

    /*void connectTo(LayerItem *otherItem);
    void connectTo(ReceiverItem *otherItem);
    void connectTo(TransmitterItem *otherItem);*/

    /*QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);*/

private:
    //QRectF m_nameRect;
    QList<NodeItem *> m_nodes;
    QList<DirectedEdgeItem *> m_edges;
    QColor m_color;
};

#endif // LAYERITEM_H
