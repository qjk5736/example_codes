// 
//   Copyright 2022 John I. Krassikoff
//   
//   This program is free software : you can redistribute it and /or modify
//   it under the terms of the GNU General Public License as published
//   by the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//   GNU General Public License for more details.
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
      if (_que.empty())
      {
        return -1;
      }
      std::lock_guard<std::mutex> guard(q_t_mutex);
      _que.pop();
      return _que.front();
    }

    void q_push(const int& item)
    {
      _que.push(item);
    }

    void q_clear()
    {
      std::lock_guard<std::mutex> guard(q_t_mutex);
      while (!_que.empty()) {
        _que.pop();
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
      *tmp_q = _que;
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
      if (_que.empty())
      {
        std::cout << "The queue is now empty." << std::endl;
      }
      else
      {
        std::cout << "The pop failed." << std::endl;
      }
    }

  public:
    std::queue<int> _que;

  };

}

#endif
