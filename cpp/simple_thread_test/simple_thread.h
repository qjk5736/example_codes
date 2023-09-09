/*
Copyright (c) 2022 John I. Krassikoff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//   
//
//  A simple thread class with simple manipulation of an int queue.
//
#ifndef simple_thread_h
#define simple_thread_h

#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <memory>

namespace SIMQ {

  std::mutex q_t_mutex;

  class simple_thread
  {
  public:
    simple_thread()
    {
    }
    // rule of zero

    void add_item(const int& nam)
    {
      int item = nam;
      std::lock_guard<std::mutex> guard(q_t_mutex);
      q_push(item);
    }

    int q_pop()
    {
      if (this->que.empty())
      {
        return -1;
      }
      std::lock_guard<std::mutex> guard(q_t_mutex);
      this->que.pop();
      return this->que.front();
    }

    void q_push(const int& item)
    {
      this->que.push(item);
    }

    void q_clear()
    {
      std::lock_guard<std::mutex> guard(q_t_mutex);
      while (!this->que.empty()) {
        this->que.pop();
      }
    }

    void run_test()
    {
      static const int num1 = 10;
      static const int num2 = 11;
      std::cout << "t1 adds " << num1 << " to the int queue." << std::endl;
      std::cout << "t2 adds " << num2 << " to the int queue." << std::endl;
      std::thread t1 = std::thread(&simple_thread::add_item, this, num1);
      std::thread t2 = std::thread(&simple_thread::add_item, this, num2);
      t1.join();
      t2.join();
      std::unique_ptr<std::queue<int>> tmp_q = std::make_unique<std::queue<int>>();
      *tmp_q = this->que;
      int q = 0;
      std::cout << "Printing the queue." << std::endl;
      while (!tmp_q->empty())
      {
        q = tmp_q->front();
        std::cout << q << "\n";
        tmp_q->pop();
      }
      std::cout << "t3 clears the queue." << std::endl;
      std::thread t3 = std::thread(&simple_thread::q_clear, this);
      t3.join();
      if (this->que.empty())
      {
        std::cout << "The queue is now empty." << std::endl;
      }
      else
      {
        std::cout << "The pop failed." << std::endl;
      }
    }

  public:
    std::queue<int> que;

  };

}

#endif
