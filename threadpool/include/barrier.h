#pragma once
#include <chrono>
#include <condition_variable>
#include <thread>

class ThreadBarrier {
 public:
  ThreadBarrier(int count) : thread_count_(count), counter_(0), waiting_(0) {}

  void Wait() {
    // fence mechanism
    std::unique_lock<std::mutex> lk(mu_);
    ++counter_;
    ++waiting_;
    cv_.wait(lk, [&] { return counter_ >= thread_count_; });
    cv_.notify_one();
    --waiting_;
    if (waiting_ == 0) {
      // reset barrier
      counter_ = 0;
    }
    lk.unlock();
  }

 private:
  std::mutex mu_;
  std::condition_variable cv_;
  int counter_;
  int waiting_;
  int thread_count_;
};
