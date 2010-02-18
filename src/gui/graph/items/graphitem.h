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

#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QGraphicsRectItem>

class GraphItem : public QGraphicsRectItem
{
public:
    enum {Type = UserType + 100};

    GraphItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void setContextMenu(QMenu *contextMenu);

    void setName(const QString &name);
    QString name() const { return m_name; }

    virtual QPointF inputPos() const;
    virtual QPointF outputPos() const;
    int type() const { return Type; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);

    QMenu *m_contextMenu;
    QString m_name;
};

#endif // GRAPHITEM_H
