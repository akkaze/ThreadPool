#include "barrier.h"
#include <chrono>
#include <iostream>
int main() {
  int thread_waiting = 3;
  ThreadBarrier barrier(thread_waiting);

  auto foo = [&barrier]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    barrier.Wait();
    std::cout << "foo" << std::endl;
  };

  auto goo = [&barrier]() {
    barrier.Wait();
    std::cout << "goo" << std::endl;
  };
  auto hoo = [&barrier]() {
    barrier.Wait();
    std::cout << "hoo" << std::endl;
  };

  std::thread t1(foo);
  std::thread t2(goo);
  std::thread t3(hoo);
  t1.join();
  t2.join();
  t3.join();
}