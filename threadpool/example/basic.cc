#include <chrono>
#include <iostream>
#include "threadpool.h"

int sleep_ms = 1000;
int main() {
    auto f = []() { std::cout << "foo\n"; };
    auto g = []() { std::cout << "goo\n"; };
    auto h = []() { std::cout << "hoo\n"; };
    auto j = []() { std::cout << "joo\n"; };

    ThreadPool pool(4);
    for (int i = 0; i < 20; i++) {
        if (i == 5) {
            pool.AddWorkers(2);
        }
        pool.AddTask(f);
    }
    pool.WaitAll();
    std::cout << "===============\n";
    for (int i = 0; i < 5; i++) {
        pool.AddTask(g);
        pool.AddTask(h);
    }
    pool.WaitAll();
    std::cout << "===============\n";
    for (int i = 0; i < 5; i++) {
        pool.AddTask(j);
    }
}
