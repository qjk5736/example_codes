//
// Copyright 2021 John I Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//

#ifndef entropy_kernel_solver_H_
#define  entropy_kernel_solver_H_

class entropy_kernel_solver
{
public:
	entropy_kernel_solver(void) { ; }
	~entropy_kernel_solver(void) = default;

	double callEntropySolver( const int Value[], const int k_elements);
};

#endif
