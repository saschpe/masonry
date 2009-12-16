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

#ifndef DIRECTEDEDGEITEM_H
#define DIRECTEDEDGEITEM_H

#include "arrowitem.h"

class NodeItem;

class DirectedEdgeItem : public ArrowItem
{
public:
    enum {Type = UserType + 3};

    DirectedEdgeItem(NodeItem *startNodeItem, NodeItem *endNodeItem, const QString &name = "", QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~DirectedEdgeItem();

    NodeItem *startNodeItem() const { return m_startNodeItem; }
    NodeItem *endNodeItem() const { return m_endNodeItem; }

public slots:
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    NodeItem *m_startNodeItem;
    NodeItem *m_endNodeItem;
};

#endif // DIRECTEDEDGEITEM_H
