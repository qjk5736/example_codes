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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PUR_posE.See the
//   GNU General Public License for more details.
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

const double DT = 0.01;						// Incremental time update 
const double M = 1.;							// Set mass to 1. for simplification
const double G = 1200000.;				// Universal gravitational constant
const int NUMBER_OF_BODIES = 3;		// Number of bodies == 3
const int DOF_PER_BODY = 3;				// x, y, z per body
const int MEASUREMENT_AXES = 2;   // No z axis in this sim. Always at 0 in initialization.

class threebody_sim
{
public:
  
  threebody_sim();
  threebody_sim(int number_of_steps, std::string filnam);
  ~threebody_sim() = default;
  threebody_sim(const threebody_sim& other) = default;            // copy constructor
  threebody_sim(threebody_sim&& other) = default;                 // move constructor
  threebody_sim& operator=(const threebody_sim& other) = default; // copy assignment
  threebody_sim& operator=(threebody_sim&& other) = default;      // move assignment

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