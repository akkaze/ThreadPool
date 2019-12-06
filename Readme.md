# ThreadPool  
轻量级的 C++11 线程池  
[![Build Status](https://travis-ci.org/akkaze/threadpool.svg?branch=master)](https://travis-ci.org/akkaze/threadpool)  
### 版权  

Public Domain。  

您可以放心的在您的项目里面使用，修改代码，不需要考虑任何额外的限制，如果我没有给出正确的版权，请联系我。  
## 概览  
`ThreadPool` 是一个动态的线程池。它能在运行时动态的修改worker的数量。同时也能在运行时等待所有任务结束并重新开始。  

## 构建  

请使用支持C++11的编译器，然后安装cmake。  

在源代码目录下面新建build文件夹，然后进入build目录，运行cmake .. && make  

您将看到basic事例，直接运行即可  

### 使用  

使用AddTask接口来将新的任务放置到线程池里进行计算，使用AddWorkers来增加工作线程的数量，使用WaitAll来等待当前任务队列里面所有任务执行完成。一个例子如下，  
 ```c++
 #include <iostream>
 #include "threadpool.h"
 
 int sleep_ms = 1000;
 int main() {
     auto f =  { std::cout << "foo\n"; };
     auto g =  { std::cout << "goo\n"; };
     auto h =  { std::cout << "hoo\n"; };
     auto j =  { std::cout << "joo\n"; };
 
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
 ```
