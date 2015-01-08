#ifndef TASKGUI_H
#define TASKGUI_H

#include <QWidget>

namespace Ui {
class TaskGui;
}
class Task;
class TaskGui : public QWidget
{
    Q_OBJECT

public:
    explicit TaskGui(QWidget *parent = 0);
    ~TaskGui();

    void connectToTask(Task* _task);

signals:
    void pauseRequested();
    void abortRequested();
    void resumeRequested();
    void startRequsted();

private slots:
    void progressChanged();//0-100
    void finished(bool ok);
    void startPauseClicked();
    void abortClicked();
    void paused();
    void aborted();
    void titleChanged(QString newTitle);
    void tooltipChanged(QString newTooltip);

private:
    Task* task;
    Ui::TaskGui *ui;
};

#endif // TASKGUI_H
