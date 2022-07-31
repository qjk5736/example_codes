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

#include "simple_thread.h"

int main()
{
    std::unique_ptr<SIMQ::simple_thread> spb = std::make_unique<SIMQ::simple_thread>();
    spb->run_test();
    return 0;
}
