#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TasksManager;
class ViewerProvider;
class Viewer3D;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QToolBar * sideToolBar;
    void setupActions();
    void setupActionsToolBar();
    void setupJobsToolDockingWidget();
    void setupInfoDockWidget();
    void setupViewer3D();

    QAction* openFileAction;
    TasksManager* tasksManager;
    Viewer3D *viewer3d;
    ViewerProvider* viewProvider;
private slots:
    void openFile();
};

#endif // MAINWINDOW_H
