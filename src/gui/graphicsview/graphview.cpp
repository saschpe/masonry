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

#include "graphview.h"
#include "graphscene.h"

GraphView::GraphView(GraphScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), m_scene(scene)
{
    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    /*setOptimizationFlags(QGraphicsView::DontClipPainter |
                         QGraphicsView::DontSavePainterState |
                         QGraphicsView::DontAdjustForAntialiasing);*/
}

GraphView::~GraphView()
{

}

/*void GraphView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (!isInteractive()) {
        painter->save();
        painter->setBrush(QBrush(QColor(60,60,60,100), Qt::Dense4Pattern));
        painter->drawRect(rect);
        painter->restore();
    }
}*/

/*void GraphView::showEvent(QShowEvent *)
{
    m_scene->resizeScene(width(), height());
}*/

/*void GraphView::resizeEvent(QResizeEvent *event)
{
    m_scene->resizeScene(event->size().width(), event->size().height());
}*/

#include "graphview.moc"
