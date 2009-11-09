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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVTKWidget.h>

#include <QHBoxLayout>

#include <vtkActor.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
    , m_vtkWidget(new QVTKWidget)
    , m_vtkRenderer(vtkRenderer::New())
{
    m_ui->setupUi(this);
    setupActions();
    m_vtkWidget->GetRenderWindow()->AddRenderer(m_vtkRenderer);

    //QHBoxLayout *layout = new QHBoxLayout;
    m_ui->centralWidget->layout()->addWidget(m_vtkWidget);
    //m_ui->centralWidget->setLayout(layout);

    // VTK test code
    vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetCenter(0.0, 0.0, 0.0);
    sphere->SetRadius(5.0);

    vtkCylinderSource *cylinder = vtkCylinderSource::New();
    cylinder->SetCenter(0.0, 0.0, 0.0);
    cylinder->SetRadius(1.0);
    cylinder->SetHeight(3.0);
    cylinder->SetResolution(20);
    vtkPolyData *polyData = cylinder->GetOutput();

    vtkPolyDataMapper *map = vtkPolyDataMapper::New();
    map->SetInput(polyData);

    vtkActor *actor = vtkActor::New();
    actor->SetMapper(map);
    actor->GetProperty()->SetColor(0, 0, 1);

    m_vtkRenderer->AddActor(actor);
    m_vtkRenderer->SetBackground(0.0, 0.0, 0.0);
    m_vtkRenderer->Render();
}

MainWindow::~MainWindow()
{
    m_vtkRenderer->Delete();
    delete m_vtkWidget;
    delete m_ui;
}

void MainWindow::setupActions()
{

}

#include "mainwindow.moc"
