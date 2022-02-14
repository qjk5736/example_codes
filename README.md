# code_snippets

A few short programs to show some of my coding styles.

1) C plus plus

alpha_beta_filter
	Implementations of basic alpha-beta filters. Build 
	with CMake.
Cholesky
	Template implementation of the Cholesky decomposition. 
	Build with Makefile.
entropy_kernel_solver
	Applies an entropy calculation for an input matrix. Build 
	with CMake where the entropy code is compiled first in to 
	a library object which is then linked to the driver.

2) Fortran

GaussJordanTest
	A program incorporating the solution of 3 simultaneous
	equations by Gauss-Jordan elimination. Uses a module to 
	contain the allocatable array and a subroutine to calculate 
	the GJE steps. Build on command line.

3) Julia

ODE_solution_comparison
	A simple program that codes solutions to an arbitrary PDE 
	using the trapezoidal, Euler and explicit Runge-Kutta 
	4th order methods. All are compared to truth and the RK4 
	solution from the DifferentialEquations.jl library.
