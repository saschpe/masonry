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
#include "gui/graph/items/nodeitem.h"

EditDockWidget::EditDockWidget(GraphScene *scene, QWidget *parent)
    : QDockWidget(parent), m_scene(scene)
    , m_selectedEdgeItem(NULL), m_selectedNodeItem(NULL)
{
    setupUi(this);

    stackedWidget->setCurrentWidget(graphPage);

    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(updateEdit()));

    connect(edgeNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setSelectedEdgeName(QString)));
    connect(nodeNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setSelectedNodeName(QString)));
    connect(nodeTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setSelectedNodeType(int)));
    deleteNodeButton->setIcon(QIcon::fromTheme("edit-delete"));
    connect(deleteNodeButton, SIGNAL(clicked()), this, SIGNAL(deleteSelectedItem()));
    deleteEdgeButton->setIcon(QIcon::fromTheme("edit-delete"));
    connect(deleteEdgeButton, SIGNAL(clicked()), this, SIGNAL(deleteSelectedItem()));
}

void EditDockWidget::updateEdit()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() == 1) {
        if (m_selectedEdgeItem = dynamic_cast<DirectedEdgeItem *>(selection.first())) {
            edgeNameLineEdit->setText(m_selectedEdgeItem->name());
            stackedWidget->setCurrentWidget(edgePage);
        } else if (m_selectedNodeItem = dynamic_cast<NodeItem *>(selection.first())) {
            nodeNameLineEdit->setText(m_selectedNodeItem->name());
            nodeTypeComboBox->setCurrentIndex(m_selectedNodeItem->nodeType());
            stackedWidget->setCurrentWidget(nodePage);
        }
    } else {
        stackedWidget->setCurrentWidget(graphPage);
    }
}

void EditDockWidget::setSelectedEdgeName(const QString &name)
{
    m_selectedEdgeItem->setName(name);
}

void EditDockWidget::setSelectedNodeName(const QString &name)
{
    m_selectedNodeItem->setName(name);
}

void EditDockWidget::setSelectedNodeType(int type)
{
    m_selectedNodeItem->setNodeType(static_cast<NodeItem::NodeType>(type));
}

#include "editdockwidget.moc"
