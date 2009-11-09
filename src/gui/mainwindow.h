#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QVTKWidget;
class vtkRenderer;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupActions();

    Ui::MainWindow *m_ui;
    QVTKWidget *m_vtkWidget;
    vtkRenderer *m_vtkRenderer;
};

#endif // MAINWINDOW_H
