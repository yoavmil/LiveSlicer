#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

#include <QDockWidget>
class TaskGui;
class QListWidget;
class Task;
class TasksManager : public QDockWidget
{
    Q_OBJECT
public:
    explicit TasksManager(QWidget *parent = 0);
    ~TasksManager();


    void AddTask(Task* t);


private:
    QWidget* widget;
    QListWidget* listWidget;
};

#endif // TASKSMANAGER_H
