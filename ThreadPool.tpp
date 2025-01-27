#ifndef THREAD_POOL_TPP
#define THREAD_POOL_TPP

template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
    auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto encapsulated_ptr =
        std::make_shared<std::packaged_task<std::invoke_result_t<F, Args...>()>>(func);
    std::future<std::invoke_result_t<F, Args...>> future_object = encapsulated_ptr->get_future();
    {
        std::unique_lock<std::mutex> lock(mutex);
        queue.emplace([encapsulated_ptr]() { (*encapsulated_ptr)(); });
    }
    cv.notify_one();
    return future_object;
}

#endif
