#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int value) : value_(value){};
    Semaphore(const Semaphore& S) : mutex_(), cv_(){};
    Semaphore(Semaphore&& S) : mutex_(), cv_(){};
    Semaphore& operator=(const Semaphore& S) {
        return *this;
    }
    ~Semaphore(){};

    void Wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (value_ > 0) {
            --value_;
        } else {
            num_waits_ += 1;
            cv_.wait(lock);
        }
    }

    void Signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (num_waits_ > 0) {
            --num_waits_;
            cv_.notify_one();
        } else {
            ++value_;
        }
    }

private:
    int value_ = 1;
    int num_waits_ = 0;
    std::mutex mutex_;
    std::condition_variable cv_;
};
