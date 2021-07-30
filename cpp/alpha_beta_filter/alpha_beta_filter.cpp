//
// Copyright 2021 DMJ Software Innovations LLC
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
//
#include "alpha_beta_filter.h"
#include <cassert>
#include <limits>

alpha_beta_filter::alpha_beta_filter()
: _alpha(0.85)
, _beta(0.005)
{
  _gamma = _beta * _beta / (2.0 * _alpha);
}

void alpha_beta_filter::initialize(double dt, double xk_1, double vxk_1, double yk_1, double vyk_1) {
  assert(dt > static_cast<double>(std::numeric_limits<float>::epsilon() )&& "Error! The time interval cannot be too small or negative.");
  _dt = dt;
  _xk_1 = xk_1;
  _vxk_1 = vxk_1;
  _yk_1 = yk_1;
  _vyk_1 = vyk_1;
  _axk_1 = 0.0;
  _ayk_1 = 0.0;
}


std::array<double, 4> alpha_beta_filter::update(double x_measurement, double y_measurement, std::array<double, 4> state) {
  // The 2D alpha-beta filter.
  double xxk = _xk_1 + (_vxk_1 * _dt);
  double vxk = _vxk_1;
  double yyk = _yk_1 + (_vyk_1 * _dt);
  double vyk = _vyk_1;
  double rkx = x_measurement - xxk;
  double rky = y_measurement - yyk;
  xxk += _alpha * rkx;
  vxk += (_beta * rkx) / _dt;
  yyk += _alpha * rky;
  vyk += (_beta * rky) / _dt;
  _xk_1 = xxk;
  _vxk_1 = vxk;
  _yk_1 = yyk;
  _vyk_1 = vyk;
  state[0] = _xk_1;
  state[1] = _vxk_1;
  state[2] = _yk_1;
  state[3] = _vyk_1;
  return state;
}

std::array<double, 6> alpha_beta_filter::update(double x_measurement, double y_measurement, std::array<double, 6> state) {
  // The 2D alpha-beta-gamma filter.
  double xxk = _xk_1 + (_vxk_1 * _dt);
  double vxk = _vxk_1;
  double axk = _axk_1;
  double yyk = _yk_1 + (_vyk_1 * _dt);
  double vyk = _vyk_1;
  double ayk = _ayk_1;
  double rkx = x_measurement - xxk;
  double rky = y_measurement - yyk;
  xxk += _alpha * rkx;
  vxk += (_beta * rkx) / _dt;
  axk += rkx * (2.0 * _gamma) / (_dt * _dt);
  yyk += _alpha * rky;
  vyk += (_beta * rky) / _dt;
  ayk += rky * (2.0 * _gamma) / (_dt * _dt);
  _xk_1 = xxk;
  _vxk_1 = vxk;
  _axk_1 = axk;
  _yk_1 = yyk;
  _vyk_1 = vyk;
  _ayk_1 = ayk;
  state[0] = _xk_1;
  state[1] = _vxk_1;
  state[2] = _axk_1;
  state[3] = _yk_1;
  state[4] = _vyk_1;
  state[5] = _ayk_1;
  return state;
}
