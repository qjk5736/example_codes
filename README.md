# code_snippets

A few example programs.

# 1) C++

## alpha_beta_filter

	Implementation of a basic alpha-beta filter with
	an algorithm extracted from the wiki page. You can 
	build this with CMake using the included 
	CMakeLists.txt.

## ch9_dynamics_cpp

	This is an C++ implementation of the algorithm in
	the Feynman Lectures on Physics Vol. I Ch. 9
	Newton's Laws of Mechanics, Section 9_6. Includes
	a gnuplot script to plot the output dat file.

## Cholesky

	A template implementation of the Cholesky decomposition.
	You can build this with the included Makefile.

## doubly_linked_list_with_reverse

	A basic doubly linked list template with a reverse function
	and some exception handling. Build from command line.

## views_and_Fibonacci

	A little fun with Fibonacci numbers. This code generates a 
	vector of Fibonacci numbers and uses std::ranges and std::views 
	syntax to square the evens and odds in separate functions 
	with Lambda expressions. Compile from the command line but you 
	will need a C++20 capable compiler with std::views.

# 2) Fortran

## GaussJordan

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

## module_sort_example

	An simple example of using modules in an executive file. 
	There are two modules. One is for a Bubble sort and the 
	other is a Selection sort. Written using Julia v1.6.5 LTS.

# 4) Python

## ch9_dynamics

	This is an implementation of the algorithm in
	the Feynman Lectures on Physics Vol. I Ch. 9
	Newton's Laws of Mechanics, Section 9_6.

## keras_1d_cnn_time_series

	A little fun with 1 dimensional CNN for processing of time-series
	data. The fitted model is used to calculate a naive prediction
	from sample test data. Uses Keras and Tensorflow.

