#include "taskqueue.h"
#include <QRunnable>
#include <QMutexLocker>
#include <QDebug>

TaskQueue::TaskQueue(const std::size_t workersCount): endFlag(false)
{
    if (workersCount < 1)
    {
        throw std::logic_error("The num of worckers below zero");
    }
    for (std::size_t i = 0; i < workersCount; i++)
    {
        workersVector.emplace_back(&TaskQueue::WorkerRun, this);
    }
}

void TaskQueue::push(AbstractTask* newTask)
{
    {
        std::unique_lock<std::mutex> lock(queueLock);
        taskQueue.emplace(newTask);
    }
    condition.notify_one();
}

void TaskQueue::wait_and_pop(std::unique_ptr<AbstractTask>& task)
{
    std::unique_lock<std::mutex> lock(queueLock);

    condition.wait(lock, [this] { return !taskQueue.empty() || endFlag; });
    if(!endFlag)
    {
        task = std::move(taskQueue.front());
        taskQueue.pop();
    }
}

bool TaskQueue::empty() const
{
    std::unique_lock<std::mutex> lock(queueLock);
    return taskQueue.empty();
}


void TaskQueue::stop()
{
    endFlag = true;
    condition.notify_all();
    qDebug() << "hi";
    for(auto&& worker: workersVector)
    {
        worker.join();
    }
}

void TaskQueue::WorkerRun()
{
    while (!endFlag)
    {
        std::unique_ptr<AbstractTask> task;
        wait_and_pop(task);
        if(!endFlag)
        {
        task.get()->execute();
        std::this_thread::yield();
        }
    }
}
