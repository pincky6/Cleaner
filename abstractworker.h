#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H


#include <QObject>
#include <QThread>
#include <QThread>

class AbstractWorker: public QObject
{
    Q_OBJECT
public:
    AbstractWorker(QObject* parent = nullptr);
    virtual void work() = 0;
    void setRunning(bool);
    void wait();
    void stopThread();
    virtual ~AbstractWorker();
signals:
    void finished();
public slots:
    void whileRun();
    void run();
protected:
    bool flag;
    QThread thread;
};

#endif // ABSTRACTWORKER_H
