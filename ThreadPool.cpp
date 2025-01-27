#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t nr_workers) : stop(false) {
    for (std::size_t i = 0; i < nr_workers; ++i) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

void ThreadPool::worker() {
    for (;;) {
        std::function<void()> cur_task;
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this]() { return stop || !queue.empty(); });

            if (stop && queue.empty())
                break;

            cur_task = queue.front();
            queue.pop();
        }
        cur_task();
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        stop = true;
    }
    cv.notify_all();
    for (auto& worker : workers) {
        worker.join();
    }
}
