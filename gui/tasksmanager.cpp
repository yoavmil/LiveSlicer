#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>

#include "tasksmanager.h"
#include "taskgui.h"
#include "task.h"
#include "logger.h"

TasksManager::TasksManager(QWidget *parent)
    : QDockWidget(parent)
{
    widget = new QWidget(this);
    widget->setLayout(new QHBoxLayout());
    listWidget = new QListWidget(widget);
    widget->layout()->addWidget(listWidget);
    this->setWidget(widget);
}

TasksManager::~TasksManager()
{

}

void TasksManager::AddTask(Task* t)
{
    TaskGui* taskGui = new TaskGui();
    taskGui->connectToTask(t);
    QListWidgetItem* lwi = new QListWidgetItem(listWidget);
    lwi->setSizeHint(taskGui->sizeHint());
    listWidget->setItemWidget(lwi, taskGui);

    //TODO start smart way
    t->Start();
}

