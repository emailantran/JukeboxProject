#include "workerthread.h"
#include <QThread>
#include <QTimer>
#include <iostream>
#include <QProcess>
#include <QVector>


WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{
    shouldStop = false;
}

WorkerThread::~WorkerThread() {
    if (process) {
        process->kill();
        process->waitForFinished();
        delete process;
    }
    this->quit();
    this->wait();
}

void WorkerThread::terminateProcess()
{
    if (process && process->state() == QProcess::Running) {
        process->terminate();
        process->waitForFinished(); // Wait for the process to finish after termination
    }
}

void WorkerThread::stop()
{
    shouldStop = true;
}

void WorkerThread::setParameter(QProcess* process, const QString &parameter)
{
    this->process = process;
    threadParameter = parameter;
}

void WorkerThread::run() {

    QString result;

    process->start(threadParameter);

    while (process->state() == QProcess::Running) {
        if (shouldStop) {
            process->kill();
            process->waitForFinished();
            process = nullptr;
            this->quit();
            break;
        }

        QThread::msleep(100);
    }

    emit resultReady(result);
}
