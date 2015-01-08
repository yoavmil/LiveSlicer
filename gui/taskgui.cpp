#include "taskgui.h"
#include "ui_taskgui.h"
#include "logger.h"
#include "task.h"

TaskGui::TaskGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskGui)
{
    ui->setupUi(this);
    connect(ui->startPauseBtn, SIGNAL(clicked()), this, SLOT(startPauseClicked()));
    connect(ui->abortBtn, SIGNAL(clicked()), this, SLOT(abortClicked()));
}

TaskGui::~TaskGui()
{
    delete ui;
}

void TaskGui::connectToTask(Task* _task)
{
    DBGF;
    task = _task;
    connect(task, SIGNAL(progressChanged()), this, SLOT(progressChanged()));
    connect(task, SIGNAL(finished(bool)), this, SLOT(finished(bool)));
    connect(task, SIGNAL(paused()), this, SLOT(paused()));
    connect(task, SIGNAL(aborted()), this, SLOT(aborted()));
    connect(task, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
    connect(task, SIGNAL(tooltipChanged(QString)), this, SLOT(tooltipChanged(QString)));
    ui->progressBar->setValue(task->GetProgress());
    DBGF;
}


void TaskGui::progressChanged()
{
    ui->progressBar->setValue(task->GetProgress());
}


void TaskGui::finished(bool ok)
{
    if (ok) {
       ui->progressBar->setValue(100);
    }
    else {

    }
}

void TaskGui::startPauseClicked()
{
    switch (task->GetTaskState() ) {
    case Task::NotStarted:
        task->Start();
        break;
    case Task::Paused:
        task->Resume();

    case Task::Running:
        task->Pause();

    default:
        break;
    }
}

void TaskGui::abortClicked()
{

}

void TaskGui::paused()
{

}

void TaskGui::aborted()
{

}

void TaskGui::titleChanged(QString newTitle)
{
    ui->title->setText(newTitle);
}

void TaskGui::tooltipChanged(QString newTooltip)
{
    this->setToolTip(newTooltip);
}
