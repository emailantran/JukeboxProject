#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QProcess>
#include <QVector>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent = nullptr);
    void setParameter(QProcess* process, const QString &parameter);
    void stop();
public slots:
    void terminateProcess();

signals:
    void resultReady(const QString &s);

protected:
    void run() override;
    ~WorkerThread();

private:
    QString threadParameter;
    QProcess* process;
    bool shouldStop;
};

#endif // WORKERTHREAD_H
