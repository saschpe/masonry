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

#include "arrowitem.h"

#include <QGraphicsScene>
#include <QPainter>

#include <cmath>
#ifdef Q_OS_WIN
#define M_PI   3.14159265358979323846   // VC++-2008 does not recognise those (standard) constants
#endif

ArrowItem::ArrowItem(const QLineF &line, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(line, parent, scene)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

ArrowItem::ArrowItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(x1, y1, x2, y2, parent, scene)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF ArrowItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;
    QRectF boundingRect = QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                                     line().p2().y() - line().p1().y()))
        .normalized().adjusted(-extra, -extra, extra, extra);
    return boundingRect.united(m_nameRect);
}

QPainterPath ArrowItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_arrowHead);
    path.addRect(m_nameRect);
    return path;
}

void ArrowItem::setName(const QString &name)
{
    m_name = name;
    update();
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p = pen();
    QBrush b(Qt::black);
    if (isSelected()) {
        p.setColor(Qt::red);
        b.setColor(Qt::red);
    }
    painter->setPen(p);
    painter->setBrush(b);

    double arrowAngle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0) {
        arrowAngle = (M_PI * 2) - arrowAngle;
    }
    qreal arrowSize = 5;
    QPointF arrowP1 = line().p2() - QPointF(sin(arrowAngle + M_PI / 3) * arrowSize,
                                            cos(arrowAngle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p2() - QPointF(sin(arrowAngle + M_PI - M_PI / 3) * arrowSize,
                                            cos(arrowAngle + M_PI - M_PI / 3) * arrowSize);
    m_arrowHead.clear();
    m_arrowHead << line().p2() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(m_arrowHead);

    // Make sure that the 'name' text is correctly aligned besides the line
    QPointF middle = line().pointAt(0.5);
    int halfLength = (line().length() - 4) / 2;
    m_nameRect = QRectF(middle.x() - halfLength, middle.y() - 10, 2 * halfLength, 20);
    qreal angle = line().angle();
    if (line().dy() >= 0) {
        m_nameRect.translate(0, 10);
    } else {
        m_nameRect.translate(0, -10);
    }
    if (angle > 30 && angle <= 90 || angle >= 270 && angle < 330) {
        m_nameRect.translate(-10, 0);
    }
    if (angle > 90 && angle < 150 || angle > 210 && angle < 270) {
        m_nameRect.translate(10, 0);
    }

    p.setColor(Qt::black);
    painter->setPen(p);
    painter->drawText(m_nameRect, Qt::AlignCenter, m_name);
}
