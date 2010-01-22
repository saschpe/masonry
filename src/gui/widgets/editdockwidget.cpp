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

#include "editdockwidget.h"
#include "gui/graph/graphscene.h"
#include "gui/graph/items/directededgeitem.h"
#include "gui/graph/items/layeritem.h"
#include "gui/graph/items/nodeitem.h"

EditDockWidget::EditDockWidget(GraphScene *scene, QWidget *parent)
    : QDockWidget(parent), m_scene(scene)
    , m_currentEdgeItem(NULL), m_currentLayerItem(NULL), m_currentNodeItem(NULL)
{
    setupUi(this);

    stackedWidget->setCurrentWidget(graphPage);

    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(updateEdit()));
    connect(edgeNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setCurrentEdgeName(QString)));
    connect(layerNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setCurrentLayerName(QString)));
    connect(nodeNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setCurrentNodeName(QString)));
}

void EditDockWidget::updateEdit()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() == 1) {
        if (m_currentEdgeItem = dynamic_cast<DirectedEdgeItem *>(selection.first())) {
            edgeNameLineEdit->setText(m_currentEdgeItem->name());
            stackedWidget->setCurrentWidget(edgePage);
        } else if (m_currentLayerItem = dynamic_cast<LayerItem *>(selection.first())) {
            layerNameLineEdit->setText(m_currentLayerItem->name());
            stackedWidget->setCurrentWidget(layerPage);
        } else if (m_currentNodeItem = dynamic_cast<NodeItem *>(selection.first())) {
            nodeNameLineEdit->setText(m_currentNodeItem->name());
            stackedWidget->setCurrentWidget(nodePage);
        }
    } else {
        stackedWidget->setCurrentWidget(graphPage);
    }
}

void EditDockWidget::setCurrentEdgeName(const QString &name)
{
    m_currentEdgeItem->setName(name);
}

void EditDockWidget::setCurrentLayerName(const QString &name)
{
    m_currentLayerItem->setName(name);
}

void EditDockWidget::setCurrentNodeName(const QString &name)
{
    m_currentNodeItem->setName(name);
}

#include "editdockwidget.moc"
