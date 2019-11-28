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

#ifndef DIRECTEDEDGEITEM_H
#define DIRECTEDEDGEITEM_H

#include "arrowitem.h"

class GraphItem;

class DirectedEdgeItem : public ArrowItem
{
public:
    enum {Type = UserType + 201};

    DirectedEdgeItem(GraphItem *start, GraphItem *end, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void setStart(GraphItem *start);
    GraphItem *start() const { return m_start; }
    void setEnd(GraphItem *end);
    GraphItem *end() const { return m_end; }
    int type() const { return Type; }

    void setFormula(const QString formula) { m_formula = formula; }
    QString formula() const { return m_formula;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    GraphItem *m_start;
    GraphItem *m_end;
    QString m_formula;
};

#endif // DIRECTEDEDGEITEM_H
