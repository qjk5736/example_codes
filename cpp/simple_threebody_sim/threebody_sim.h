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
//  This is an implementation of the threebody algorithm in
//  Projects in Scientific Computation, Richard Crandall, 1994
//  Section 2_4_1.
// 
//  filename threebody_sim.h
// 
//  Can run from the command line as: 
//  threebody_sim.exe x0 y0 z0 vx0 vy0 vz0 x1 y1 z1 vx1 vy1 vz1 x2 y2 z2 vx2 vy2 vz2 N
//

#ifndef threebody_cpp_h_
#define threebody_cpp_h_

#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <iomanip>

namespace TBDY{

const double DT = 0.001;					        // Incremental time update seconds
const double GRAV_CONST = 6.674E-11;       // Gravitational constant newtons*meter*meter/
const int NUMBER_OF_BODIES = 3;		        // Number of bodies == 3
const int DOF_PER_BODY = 3;				        // x, y, z per body
const int MEASUREMENT_AXES = 2;           // Only x and y coordinates from measuremnts.

class threebody_sim
{
public:
  
  threebody_sim();
  threebody_sim(int number_of_steps, std::string filnam);
  ~threebody_sim() = default;
  threebody_sim(const threebody_sim& other) = delete;            // copy constructor
  threebody_sim(threebody_sim&& other) = delete;                 // move constructor
  threebody_sim& operator=(const threebody_sim& other) = delete; // copy assignment
  threebody_sim& operator=(threebody_sim&& other) = delete;      // move assignment

  void run_simulation(int argc, char** argv);

private:

  int N;
  std::string filenam;
  std::array<std::array<double, DOF_PER_BODY>, NUMBER_OF_BODIES> pos;
  std::array<std::array<double, DOF_PER_BODY>, NUMBER_OF_BODIES> vel;
  std::array<std::array<double, DOF_PER_BODY>, NUMBER_OF_BODIES> acc;
  std::array<std::array<double, DOF_PER_BODY>, NUMBER_OF_BODIES> residual;
  std::array<double, NUMBER_OF_BODIES> r_vec;
  std::array<double, NUMBER_OF_BODIES> func;
  std::array<double, NUMBER_OF_BODIES> mass;

  void print_header();
  void print_3_body_positions();
  void update_position();
  void initialize_from_cmd_line(char** argv);
  void initialize_from_definition();
  
  std::ofstream output_file;

};

}

#endif