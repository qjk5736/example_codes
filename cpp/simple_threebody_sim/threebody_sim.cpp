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
		: N(1000)
		, filenam("default_threebody_positions.dat")
	{
		this->pos = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->vel = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->acc = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->residual = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->r_vec = { {0., 0., 0.} };
		this->func = { {0., 0., 0.} };
		this->mass = { {0., 0., 0.} };
	}

	threebody_sim::threebody_sim(int number_of_steps, std::string filnam)
		: N(number_of_steps)
		, filenam(filnam)
	{
		this->pos = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->vel = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->acc = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->residual = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
		this->r_vec = { {0., 0., 0.} };
		this->func = { {0., 0., 0.} };
		this->mass = { {0., 0., 0.} };
	}

	void threebody_sim::print_header()
	{
		std::cout << "x1 y1 z1 x2 y2 z2 x3 y3 z3" << std::endl;
		if (this->output_file)
			this->output_file << "x1 y1 z1 x2 y2 z2 x3 y3 z3" << std::endl;
	}

	void threebody_sim::print_3_body_positions()
	{
		std::cout << std::fixed;
		for (int j = 0; j < NUMBER_OF_BODIES; j++)
		{
			for (int i = 0; i < DOF_PER_BODY; i++)
			{
				std::cout << std::setprecision(6) << this->pos[j][i] << " ";
				if (this->output_file)
					this->output_file << std::setprecision(6) << this->pos[j][i] << " ";
			}
		}
		std::cout << std::endl;
		if (this->output_file)
			this->output_file << std::endl;
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
			this->r_vec[j] = 0;
			for (i = 0; i < DOF_PER_BODY; i++)
			{
				this->residual[j][i] = this->pos[k][i] - this->pos[j][i];
				this->r_vec[j] += this->residual[j][i] * this->residual[j][i];
			}
			// f'() = (-)G*M*m/(r^3/2), residual term is included in the position update.
			this->func[j] = -GRAV_CONST * this->mass[k] * this->mass[j] / (this->r_vec[j] * std::sqrt(this->r_vec[j]));
		}
		for (j = 0; j < NUMBER_OF_BODIES; j++)
		{
			k = (j + 2) % NUMBER_OF_BODIES;
			for (i = 0; i < DOF_PER_BODY; i++)
			{
				// a = sum( f'() * residual ) eq. 2.4.3
				this->acc[j][i] = this->func[k] * this->residual[k][i] - this->func[j] * this->residual[j][i];
				// v = d * dt									eq. 2.4.3
				this->vel[j][i] += this->acc[j][i] * DT;
				// p = v * dt									eq. 2.4.3
				this->pos[j][i] += this->vel[j][i] * DT;
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
				this->pos[j][i] = std::atoi(argv[arg_index]);
				this->vel[j][i] = std::atoi(argv[arg_index + 2]);
				arg_index++;
			}
			this->mass[j] = 10*j;
		}
		this->N = std::atoi(argv[arg_index]);
	}

	void threebody_sim::initialize_from_definition()
	{
		// Set the pre-defined test parameters.
		// Body 1
		this->pos[0][0] = 75.00;
		this->pos[0][1] = 0.;
		this->pos[0][2] = 0.;
		this->vel[0][0] = 0.;
		this->vel[0][1] = 75.00;
		this->vel[0][2] = 0;
		// Body 2
		this->pos[1][0] = -37.50;
		this->pos[1][1] = 65.25;
		this->pos[1][2] = 0.;
		this->vel[1][0] = -65.25;
		this->vel[1][1] = -37.50;
		this->vel[1][2] = 0;
		// Body 3
		this->pos[2][0] = -37.50;
		this->pos[2][1] = -65.25;
		this->pos[2][2] = 0.;
		this->vel[2][0] = 65.25;
		this->vel[2][1] = -37.50;
		this->vel[2][2] = 0;
		// mass vector (M1, M2, M3) kg
		this->mass[0] = 10;
		this->mass[1] = 20;
		this->mass[2] = 30;
		// Number of steps to simulate.
		this->N = 10000;
	}

	void threebody_sim::run_simulation(int argc, char** argv)
	{
		if (argc < 5)
			initialize_from_definition();
		else
			initialize_from_cmd_line(argv);
		this->output_file.open(this->filenam.c_str());
		print_header();
		for (int sim_index = 0; sim_index < this->N; sim_index++)
		{
			//update_physics();
			update_position();
			print_3_body_positions();
		}
		if(this->output_file) this->output_file.close();
	}

}

#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<TBDY::threebody_sim> sim = std::make_unique<TBDY::threebody_sim>(100,"threebody_positions_06252002.dat");
	sim->run_simulation(argc, argv);
	return 0;
}
