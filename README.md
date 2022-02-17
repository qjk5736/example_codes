# code_snippets

A few short programs to showcase some of my coding styles.

# 1) C++

## alpha_beta_filter

	Implementation of a basic alpha-beta filter from the 
	wiki page. You can build this with CMake using the 
	included CMakeLists.txt.
	
## Cholesky

	A template implementation of the Cholesky decomposition.
	You can build this with the included Makefile.

## entropy_kernel_solver

	Applies an entropy calculation for an input matrix. Build 
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

# 3) Julia

## ODE_solution_comparison

	A simple program that codes solutions to an arbitrary PDE 
	using the trapezoidal, Euler and explicit Runge-Kutta 
	4th order methods. All are compared to truth and the RK4 
	solution from the DifferentialEquations.jl library.
