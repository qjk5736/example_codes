#
#   Copyright 2022 John I. Krassikoff
#   
#   This program is free software : you can redistribute it and /or modify
#   it under the terms of the GNU General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#   GNU General Public License for more details.
#   
#   A simple program that codes solutions to an arbitrary PDE 
#   using the trapezoidal, Euler and explicit Runge-Kutta 
#   4th order methods. All are compared to truth and the RK4 
#   solution from the DifferentialEquations.jl lbrary.
#
using Random

include("Utils/Bubblesort.jl")
include("Utils/Selectionsort.jl")
rng = MersenneTwister(1234);
x = rand(rng, 1:10,10)

println("\nx: ", x)
bSorted = ModBubblesort.sort(copy(x))
println("y: ",bSorted) 

println("\nx: ", x)
y = ModSelectionsort.sort(copy(x))
println("y: ", y)
