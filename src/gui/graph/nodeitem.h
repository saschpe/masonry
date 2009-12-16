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

#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsEllipseItem>

class DirectedEdgeItem;

class NodeItem : public QGraphicsEllipseItem
{
public:
    enum {Type = UserType + 1};

    NodeItem(const QString &name = "", QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NodeItem();

    void setContextMenu(QMenu *contextMenu) { m_contextMenu = contextMenu; }

    void addEdgeItem(DirectedEdgeItem *item);
    void removeEdgeItem(DirectedEdgeItem *item);
    void removeEdgeItems();

    void setName(const QString &name);
    QString name() const { return m_name; }
    void setRadius(qreal radius);
    qreal radius() const { return m_radius; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QMenu *m_contextMenu;
    QList<DirectedEdgeItem *> m_edgeItems;
    QString m_name;
    qreal m_radius;
};

#endif // NODEITEM_H
