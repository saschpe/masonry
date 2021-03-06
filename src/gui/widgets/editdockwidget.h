/*
    Copyright (c) 2009 ifak - Institut für Automation und Kommunikation e.V.
    Copyright (c) 2009 Sascha Peilicke <sascha@peilicke.de>

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

#ifndef EDITDOCKWIDGET_H
#define EDITDOCKWIDGET_H

#include "ui_editdockwidget.h"

#include <QDockWidget>

class DirectedEdgeItem;
class GraphScene;
class NodeItem;

/**
 * This dock widget allows to modify nodes and edges of a Mason graph
 * that are part of a GraphScene (e.g. NodeItem and DirectEdgeItem instances).
 *
 * @author Sascha Peilicke <sascha@peilicke.de>
 */
class EditDockWidget : public QDockWidget, private Ui::EditDockWidget
{
    Q_OBJECT

public:
    EditDockWidget(GraphScene *scene, QWidget *parent = 0);

signals:
    void deleteSelectedItem();

private slots:
    void updateWidget();

    void setSelectedEdgeName(const QString &);
    void setSelectedEdgeFormula();
    void setSelectedNodeName(const QString &);
    void setSelectedNodeFormula();
    void setSelectedNodeType(int);

private:
    GraphScene *m_scene;
    DirectedEdgeItem *m_selectedEdgeItem;
    NodeItem *m_selectedNodeItem;
};

#endif // EDITDOCKWIDGET_H
