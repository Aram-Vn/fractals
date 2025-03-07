#ifndef __FRACTALS_INCLUDE_THREAD_POOL_H__
#define __FRACTALS_INCLUDE_THREAD_POOL_H__

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(std::size_t numThreads);
    ~ThreadPool();

public:
    void        enqueue(std::function<void()> task);
    std::size_t getNumThreads() const
    {
        return m_numThreads;
    }

private:
    std::vector<std::thread>          workers;
    std::queue<std::function<void()>> tasks;
    std::mutex                        queueMutex;
    std::condition_variable           condition;
    std::size_t                       m_numThreads;
    bool                              stop = false;
};

#endif // __FRACTALS_INCLUDE_THREAD_POOL_H__