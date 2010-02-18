/*
    Copyright (c) 2009-2010 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009-2010 Sascha Peilicke <sasch.pe@gmx.de>

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

#include "graphitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

GraphItem::GraphItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent, scene)
    , m_contextMenu(NULL)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(QColor(0, 0, 255, 10));
}

void GraphItem::setContextMenu(QMenu *contextMenu)
{
    m_contextMenu = contextMenu;
}

void GraphItem::setName(const QString &name)
{
    m_name = name;
    update();
}

QPointF GraphItem::inputPos() const
{
    return pos();
}

QPointF GraphItem::outputPos() const
{
    return pos();
}

void GraphItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_contextMenu) {
        return;
    }
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}
