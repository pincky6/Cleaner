#include "abstractworker.h"

AbstractWorker::AbstractWorker(QObject* parent ):
    QObject(parent), flag(true)
{

}

void AbstractWorker::setRunning(bool newRunning)
{
    if (flag == newRunning)
        return;
    flag = newRunning;
}

void AbstractWorker::wait()
{
    emit finished();
    while(thread.isRunning());
}

void AbstractWorker::stopThread()
{
    setRunning(false);
    wait();
}

AbstractWorker::~AbstractWorker()
{
    stopThread();
}

void AbstractWorker::whileRun()
{
    while(flag)
    {
        work();
        thread.sleep(5);
    }
    emit finished();
}

void AbstractWorker::run()
{
    work();
}
