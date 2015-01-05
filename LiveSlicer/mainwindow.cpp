#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meshloader.h"
#include "taskgui.h"
#include "logger.h"
#include "tasksmanager.h"
#include "viewer3d.h"
#include "viewerprovider.h"
#include "mesh.h"
#include "viewworld.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Live Slicer");
    setupActions();
    setupActionsToolBar();
    setupInfoDockWidget();
    setupViewer3D();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    openFileAction = new QAction(QIcon(":/images/resources/folder_open.png"), "&Open file", this);
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::setupActionsToolBar()
{
    sideToolBar = new QToolBar(this);
    sideToolBar->addAction(openFileAction);
    ui->actionsDockWidget->setWidget(sideToolBar);
}

void MainWindow::setupInfoDockWidget()
{
    tasksManager = new TasksManager(this);
    this->addDockWidget(Qt::RightDockWidgetArea, tasksManager);
}

void MainWindow::setupViewer3D()
{
    viewer3d = ui->viewer3d;
    viewProvider = new ViewerProvider(this);
    ViewWorld* vw = new ViewWorld(viewProvider);
    viewProvider->AddItem(vw);
    viewer3d->SetProvider(viewProvider);
}

void MainWindow::openFile()
{
    QStringList filters;
    filters << "stl (*.stl)";
    QFileDialog * openFileDialog = new QFileDialog(this, "open mesh file");

    openFileDialog->setNameFilters(filters);
    if (openFileDialog->exec()) {
        QStringList fNames = openFileDialog->selectedFiles();
        for (int i = 0; i < fNames.length(); i++) {
            MeshLoaderParams mlp(fNames[i]);
            mlp.ignoreNormals = false;
            mlp.mesh = new Mesh();
            mlp.viewProvider = viewProvider;
            MeshLoader* ml = new MeshLoader(mlp);
            tasksManager->AddTask(ml);
        }
    }
}
