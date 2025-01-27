#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>


class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<std::function<void()>> queue;
    void worker();
    bool stop;
public:
    ThreadPool(std::size_t nr_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
	template<typename F, typename... Args>
	auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;
    ThreadPool(ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};

#include "ThreadPool.tpp"
#endif
