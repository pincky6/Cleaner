#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Task.h"

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <condition_variable>


class TaskQueue
{
public:
    explicit TaskQueue(const std::size_t threadCount = 2);
    void push(AbstractTask* newTask);
    void wait_and_pop(std::unique_ptr<AbstractTask>& task);

    void stop();
    bool empty() const;
private:
    void WorkerRun();
private:
    std::queue<std::unique_ptr<AbstractTask> > taskQueue;
    std::vector<std::thread> workersVector;
    std::condition_variable condition;
    mutable std::mutex queueLock;
    bool endFlag;
};
#endif

