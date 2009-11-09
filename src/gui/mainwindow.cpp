#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVTKWidget.h>

#include <QHBoxLayout>

#include <vtkActor.h>
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

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_vtkWidget);
    m_ui->centralWidget->setLayout(layout);

    // VTK test code
    vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetCenter(0.0, 0.0, 0.0);
    sphere->SetRadius(5.0);
    vtkPolyData *polyData = sphere->GetOutput();

    vtkPolyDataMapper *map = vtkPolyDataMapper::New();
    map->SetInput(polyData);

    vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(map);
    sphereActor->GetProperty()->SetColor(0, 0, 1);

    m_vtkRenderer->AddActor(sphereActor);
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
