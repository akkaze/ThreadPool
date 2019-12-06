#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    using Task = std::function<void(void)>;
    using TaskQueue = std::queue<Task>;
    // Constructor
    ThreadPool(const size_t& num_workers);

    // Deconstructor
    ~ThreadPool();
    /**
     * @brief: Add new workers to worker queue
     *
     * @param num_new_workers number of new workers
     */
    void AddWorkers(const size_t& num_new_workers);
    /**
     * @brief: Add a task to queue
     * The function will add, at the end of the queue, a 'void'
     * function only if no one is waiting for stop
     * @param: task: task function
     */
    void AddTask(const Task& task);

    size_t JobsRemaining();

    void Run();

    Task NextJob();
    /**
     *  @brief: Join with all threads. Block until all threads have completed.
     *  @Params: wait_for_all: If true, will wait for the queue to empty
     *          before joining with threads. If false, will complete
     *          current jobs, then inform the threads to exit.
     *  The queue will be empty after this call, and the threads will
     *  be done. After invoking `ThreadPool::JoinAll`, the pool can no
     *  longer be used. If you need the pool to exist past completion
     *  of jobs, look to use `ThreadPool::WaitAll`.
     */
    void JoinAll(const bool& wait_for_all = true);

    /**
     *  @brief: Wait for the pool to empty before continuing.
     *  This does not call `std::thread::join`, it only waits until
     *  all jobs have finshed executing.
     */
    void WaitAll();

    size_t num_workers() const;
private:
    std::atomic_int jobs_left_;
    std::atomic_bool bailout_;
    std::atomic_bool finished_;
    std::condition_variable job_available_var_;
    std::condition_variable wait_var_;
    std::mutex wait_mutex_;
    std::mutex queue_mutex_;
    std::mutex worker_mutex_;
    std::vector<std::thread> workers_;
    size_t num_workers_;
    // where tasks are storage
    TaskQueue task_queue_;
};
