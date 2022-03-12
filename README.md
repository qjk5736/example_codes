# code_snippets

A few simple example programs.

# 1) C++

## alpha_beta_filter

	Implementation of a basic alpha-beta filter from the 
	wiki page. You can build this with CMake using the 
	included CMakeLists.txt.
	
## Cholesky

	A template implementation of the Cholesky decomposition.
	You can build this with the included Makefile.

## entropy_kernel_solver

	Applies an entropy calculation for an input kernel. Build 
	with CMake where the entropy code is compiled first in to 
	a library object which is then linked to the driver. The 
	simple CMakeLists.txt is included.

# 2) Fortran

## GaussJordanTest

	A program incorporating the solution of 3 simultaneous
	equations by Gauss-Jordan elimination. Uses a module to 
	contain the allocatable array and a subroutine to calculate 
	the GJE steps. Build on command line with the command listed
	in the file.

## Objects

	A simple program showing a little OOP capability. Includes a
	driver file and a module. Build on command line with command
	listed in the main.f90 file.

## Simple_Class

	A simple Fortran type(class). Build from command line.

# 3) Julia

## ODE_solution_comparison

	A simple program that codes solutions to an arbitrary PDE 
	using the trapezoidal, Euler, explicit Runge-Kutta 
	4th order methods and the ODE library implementation. All 
	are compared to truth. Written using Julia v1.6.5 LTS.
