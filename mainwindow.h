#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Mesh;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Open_Mesh_triggered();

private:
    Ui::MainWindow *ui;
    Mesh* mesh;
};

#endif // MAINWINDOW_H
