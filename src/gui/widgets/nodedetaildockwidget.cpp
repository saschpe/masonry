/*
    Copyright (c) 2009 ifak - Institut für Automation und Kommunikation e.V.
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

#include "nodedetaildockwidget.h"
#include "gui/graph/graphscene.h"
#include "gui/graph/items/nodeitem.h"

NodeDetailDockWidget::NodeDetailDockWidget(GraphScene *scene, QWidget *parent)
    : QDockWidget(parent), m_scene(scene)
{
    setupUi(this);

    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(updateWidget()));
}

void NodeDetailDockWidget::updateWidget()
{
    const QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() == 1) {
        if (m_selectedNodeItem = qgraphicsitem_cast<NodeItem *>(selection.first())) {
            nodeNameLineEdit->setText(m_selectedNodeItem->name());
        }
    } else {
    }
}

#include "nodedetaildockwidget.moc"
