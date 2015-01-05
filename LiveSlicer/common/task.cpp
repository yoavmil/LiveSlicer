#include <QMutexLocker>
#include <QThread>
#include <QDebug>

#include "logger.h"
#include "task.h"

QMutex Task::allJobsMutex;
QObjectList Task::alljobs;

Task::Task(bool _threaded):
    QObject(NULL),
    pauseRequested(false),
    abortRequested(false),
    thread(NULL),
    threaded(_threaded),
    taskState(NotStarted)
{

    QMutexLocker ml(&Task::allJobsMutex);
    Task::alljobs << this;

    if (threaded) {
        thread = new QThread(NULL);
        this->moveToThread(thread);
        thread->start();
    }

    connect(this, SIGNAL(startSig()), this, SLOT(doStart()), Qt::QueuedConnection);
    connect(this, SIGNAL(resumeSig()), this, SLOT(doResume()), Qt::QueuedConnection);
}

Task::~Task()
{
    QMutexLocker ml(&Task::allJobsMutex);
    Task::alljobs.removeOne(this);
    if (thread)
        thread->deleteLater();
}

int Task::GetProgress()
{
    return 0;
}

bool Task::IsFinished()
{
    return false;
}

void Task::Start()
{
    taskState = Running;
    emit startSig();
}

void Task::Pause()
{
    pauseRequested = true;
}

void Task::Resume()
{
    pauseRequested = false;
    emit resumeSig();
}

void Task::Abort()
{
    abortRequested = true;
}

void Task::setProgress(int p)
{
    if (currProgress != p) {
        currProgress = p;
        emit progress(currProgress);
    }
}
void Task::setProgress(double p)
{
    setProgress(qRound(p));
}

void Task::setTitle(QString str)
{
    if (title != str) {
        title = str;
        emit titleChanged(title);
    }
}

void Task::setTooltip(QString str)
{
    if (tooltip != str) {
        tooltip = str;
        emit tooltipChanged(tooltip);
    }
}

