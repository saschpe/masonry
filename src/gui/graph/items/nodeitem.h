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

#ifndef NODEITEM_H
#define NODEITEM_H

#include "graphitem.h"

#include <QGraphicsLayoutItem>

class NodeItem : public GraphItem, public QGraphicsLayoutItem
{
public:
    enum {Type = UserType + 101};
    enum NodeType {
        InputNode,
        OutputNode,
        StandardNode
    };

    NodeItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void setGeometry(const QRectF &rect);
    void setRadius(qreal radius);
    qreal radius() const { return m_radius; }
    void setNodeType(NodeType nodeType);
    NodeType nodeType() const { return m_nodeType; }
    int type() const { return Type; }

    void setFormula(const QString formula) { m_formula = formula; }
    QString formula() const { return m_formula;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraints = QSizeF()) const;

private:
    qreal m_radius;
    NodeType m_nodeType;
    QString m_formula;
};

#endif // NODEITEM_H
