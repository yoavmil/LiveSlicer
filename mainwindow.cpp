#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "mesh.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mesh(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_Mesh_triggered()
{
    QString fName = QFileDialog::getOpenFileName(
                this,
                "Load Mesh",
                Settings::LastMeshDir(),
                "Mesh (*.stl *.STL)");
     if (fName.isEmpty())
         return;
     Settings::LastMeshDir(QFileInfo(fName).absolutePath());
     mesh = new Mesh(this);
     ui->viewer->SetMesh(mesh);
     mesh->Load(fName);
}
