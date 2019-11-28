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

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

class GraphScene;

/**
 * This class represents a view on a graph scene. It
 * provides mostly zooming support and sets some
 * optimization flags.
 *
 * @author Sascha Peilicke <sascha@peilicke.de>
 * @since 0.1
 */
class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(GraphScene *scene, QWidget *parent = 0);

public slots:
    void zoomToFit();
    void zoomIn();
    void zoomOut();

signals:
    void zoomChanged();

protected:
    void wheelEvent(QWheelEvent *);

    GraphScene * const m_scene;
};

#endif // GRAPHVIEW_H
