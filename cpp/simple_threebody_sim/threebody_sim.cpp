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
//  filename threebody_sim.cpp
// 
//  Can run from the command line as: 
//  threebody_sim.exe x0 y0 z0 vx0 vy0 vz0 x1 y1 z1 vx1 vy1 vz1 x2 y2 z2 vx2 vy2 vz2 N
//

#include "threebody_sim.h"

namespace TBDY {

	threebody_sim::threebody_sim()
		: _N(1000)
		, _filenam("default_threebody_positions.dat")
	{
		_pos = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_vel = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_acc = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_residual = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_r_vec = { {0., 0., 0.} };
		_func = { {0., 0., 0.} };
		_mass = { {0., 0., 0.} };
	}

	threebody_sim::threebody_sim(int number_of_steps, std::string filnam)
		: _N(number_of_steps)
		, _filenam(filnam)
	{
		_pos = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_vel = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_acc = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_residual = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		_r_vec = { {0., 0., 0.} };
		_func = { {0., 0., 0.} };
		_mass = { {0., 0., 0.} };
	}

	void threebody_sim::print_header()
	{
		std::cout << "x1 y1 z1 x2 y2 z2 x3 y3 z3" << std::endl;
		if (_output_file)
			_output_file << "x1 y1 z1 x2 y2 z2 x3 y3 z3" << std::endl;
	}

	void threebody_sim::print_3_body_positions()
	{
		std::cout << std::fixed;
		for (int j = 0; j < NUMBER_OF_BODIES; j++)
		{
			for (int i = 0; i < DOF_PER_BODY; i++)
			{
				std::cout << std::setprecision(6) << _pos[j][i] << " ";
				if (_output_file)
					_output_file << std::setprecision(6) << _pos[j][i] << " ";
			}
		}
		std::cout << std::endl;
		if (_output_file)
			_output_file << std::endl;
	}

	void threebody_sim::update_position()
	{
		int i = 0;
		int j = 0;
		int k = 0;
		// f() = (-)G*M*m*r/(r^3/2) eq. 2.4.1
		for (j = 0; j < NUMBER_OF_BODIES; j++)
		{
			k = (j + 1) % NUMBER_OF_BODIES;
			_r_vec[j] = 0;
			for (i = 0; i < DOF_PER_BODY; i++)
			{
				_residual[j][i] = _pos[k][i] - _pos[j][i];
				_r_vec[j] += _residual[j][i] * _residual[j][i];
			}
			// f'() = (-)G*M*m/(r^3/2), _residual term is included in the _position update.
			_func[j] = -G * _mass[k] * _mass[j] / (_r_vec[j] * std::sqrt(_r_vec[j]));
		}
		for (j = 0; j < NUMBER_OF_BODIES; j++)
		{
			k = (j + 2) % NUMBER_OF_BODIES;
			for (i = 0; i < DOF_PER_BODY; i++)
			{
				// a = sum( f'() * _residual ) eq. 2.4.3
				_acc[j][i] = _func[k] * _residual[k][i] - _func[j] * _residual[j][i];
				// v = d * dt									eq. 2.4.3
				_vel[j][i] += _acc[j][i] * DT;
				// p = v * dt									eq. 2.4.3
				_pos[j][i] += _vel[j][i] * DT;
			}
		}
	}

	void threebody_sim::initialize_from_cmd_line(char** argv)
	{
		/* Read in command line parameters */
		int arg_index = 1;
		for (int j = 0; j < NUMBER_OF_BODIES; j++)
		{
			for (int i = 0; i < MEASUREMENT_AXES; i++)
			{
				_pos[j][i] = std::atoi(argv[arg_index]);
				_vel[j][i] = std::atoi(argv[arg_index + 2]);
				arg_index++;
			}
			_mass[j] = M;
		}
		_N = std::atoi(argv[arg_index]);
	}

	void threebody_sim::initialize_from_definition()
	{
		// Set the pre-defined test parameters.
		// Body 1
		_pos[0][0] = 75.00;
		_pos[0][1] = 0.;
		_pos[0][2] = 0.;
		_vel[0][0] = 0.;
		_vel[0][1] = 75.00;
		_vel[0][2] = 0;
		// Body 2
		_pos[1][0] = -37.50;
		_pos[1][1] = 65.25;
		_pos[1][2] = 0.;
		_vel[1][0] = -65.25;
		_vel[1][1] = -37.50;
		_vel[1][2] = 0;
		// Body 3
		_pos[2][0] = -37.50;
		_pos[2][1] = -65.25;
		_pos[2][2] = 0.;
		_vel[2][0] = 65.25;
		_vel[2][1] = -37.50;
		_vel[2][2] = 0;
		// _mass vector (M1, M2, M3)
		_mass[0] = M;
		_mass[1] = M;
		_mass[2] = M;
		// Number of steps to simulate.
		_N = 100;
	}

	void threebody_sim::run_simulation(int argc, char** argv)
	{
		if (argc < 5)
			initialize_from_definition();
		else
			initialize_from_cmd_line(argv);
		_output_file.open(_filenam.c_str());
		print_header();
		for (int sim_index = 0; sim_index < _N; sim_index++)
		{
			//update_physics();
			update_position();
			print_3_body_positions();
		}
		if(_output_file) _output_file.close();
	}

}

#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<TBDY::threebody_sim> sim = std::make_unique<TBDY::threebody_sim>(100,"threebody_positions_06252002.dat");
	sim->run_simulation(argc, argv);
	return 0;
}
