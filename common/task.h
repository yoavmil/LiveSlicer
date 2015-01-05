#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QMutex>
#include <QObjectList>
class QThread;

class Task : public QObject
{
    Q_OBJECT

public:
    Task(bool _threaded);
    virtual ~Task();
    virtual int GetProgress();
    virtual bool IsFinished();
    virtual QString GetTitle() {return title;}
    virtual QString GetTooltip() {return tooltip;}

    enum TaskState {
        NotStarted,
        Running,
        Paused,
        Finished,
        Aborted
    };

    TaskState GetTaskState() {return taskState;}

    virtual bool CanPause() { return false; }
    virtual bool CanAbort() { return false; }

    Q_ENUMS(TaskState)

signals:
    void progress(int donePrecent);//0-100
    void finished(bool ok);
    void paused();
    void aborted();
    void titleChanged(QString newTitle);
    void tooltipChanged(QString newTooltip);

public:
    void Start();
    void Pause();
    void Resume();
    void Abort();

signals:
    void startSig();
    void resumeSig();

protected:
    QThread* thread;
    bool pauseRequested;
    bool abortRequested;
    void setProgress(int p);
    void setProgress(double p);
    void setTitle(QString str);
    void setTooltip(QString str);

    class PausedException {};
    class AbortedException {};

    bool threaded;

protected slots:
    virtual void doStart() = 0;
    virtual void doResume() = 0;

private:
    static QMutex allJobsMutex;
    static QObjectList alljobs;
    int currProgress;
    QString title, tooltip;
    TaskState taskState;
};

#endif // JOB_H