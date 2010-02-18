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

#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsLineItem>

class ArrowItem : public QGraphicsLineItem
{
public:
    enum {Type = UserType + 200};

    ArrowItem(const QLineF &line, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    ArrowItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void setName(const QString &name);
    QString name() const { return m_name; }
    int type() const { return Type; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QPolygonF m_arrowHead;
    QRectF m_nameRect;
    QString m_name;
};

#endif // ARROWITEM_H
