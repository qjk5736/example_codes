//
// Copyright 2021 John I Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//
// This algorithm was derived and extended from 
// text at: https://en.wikipedia.org/wiki/Alpha_beta_filter
// governed by the Creative Commons Attribution-ShareAlike License
//
#pragma once

#include <array>

class alpha_beta_filter
{
public:
  alpha_beta_filter();

  void initialize(double dt, double xk_1, double vx_1, double yk_1, double vy_1);
  std::array<double, 4> update(double i, double j, std::array<double, 4> state); // alpha-beta filter
  std::array<double, 6> update(double i, double j, std::array<double, 6> state); // alpha-beta-gamma filter
private:
  double _dt = 0.033;
  double _xk_1 = 0;
  double _vxk_1 = 0;
  double _axk_1 = 0;
  double _yk_1 = 0;
  double _vyk_1 = 0;
  double _ayk_1 = 0;
  double _alpha = 0.85;
  double _beta = 0.005;
  double _gamma = 0.0;
};

