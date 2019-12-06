#include "semaphore.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
int num_workers = 10;
Semaphore sema(0);
int worker_count = 0;
void func(int id) {
    worker_count += 1;
    if (worker_count < num_workers) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        sema.Wait();
    }
    std::cout << id << '\n';
    if (worker_count > 0) {
        sema.Signal();
    }
}


int main() {
    std::vector<std::thread> ths;
    for (int i = 0; i < num_workers; i++) {
        ths.emplace_back(std::thread(std::bind(func, i)));
    }
    for (auto& th : ths) {
        th.join();
    }
    return 0;
}
