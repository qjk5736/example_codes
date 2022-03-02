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

using Plots
using DifferentialEquations

function trapezoidal(f::Function, y0::Real, a::Real, h::Real, M::Int64)
    N = M + 1
    y = zeros(N,2)
    y[1,1] = a
    y[1,2] = y0
    i = 2
    while i <= N
        y[i,2] = f(y[i-1,1],y[i-1,2]) +h*((y[i-1,2]+y[1,2])/2)
        y[i,1] = a +(i-1)*h
        i += 1
    end
    return y
end

function euler(f::Function, y0::Real, a::Real, h::Real, M::Int64)
    N = M + 1
    y = zeros(N,2)
    y[1,1] = a
    y[1,2] = y0
    i = 2
    while i <= N
        y[i,2] = y[i-1,2] + h*f(y[i-1,1],y[i-1,2])
        y[i,1] = a +(i-1)*h
        i += 1
    end
    return y
end

function explicit_rk4o(f::Function, y0::Real, a::Real, h::Real, M::Int64)
    N = M + 1
    y = zeros(N,2)
    y[1,1] = a
    y[1,2] = y0
    i = 2
    while i <= N
        k1 = h*f(y[i-1,1], y[i-1,2])
        k2 = h*f(y[i-1,1] + h/2, y[i-1,2] + k1/2)
        k3 = h*f(y[i-1,1] + h/2, y[i-1,2] + k2/2)
        k4 = h*f(y[i-1,1] + h, y[i-1,2] + k3)
        y[i,1] = a + (i-1)*h
        y[i,2] = y[i-1,2] + (k1 + 2 * k2 + 2 * k3 + k4)/6
        i += 1
    end
    return y
end


function one_ode()
    f(t) = 1 - 0.5*exp(t) + t^2
    df(t,y) = y -1 + 2*t - t^2
    y0 = 0.5
    a = 0
    b = 5
    max_points = 10
    h = (b-a)/max_points
    trap_solution = trapezoidal(df, y0, a, h, max_points)
    euler_solution = euler(df, y0, a, h, max_points)
    rk4o_solution = explicit_rk4o(df, y0, a, h, max_points)
    plot_range = a:0.2:b
    Plots.plot(plot_range, f.(plot_range), label="f(t)", line=(:dot, 2), framestyle=:box, legend=:bottomleft, dpi=600)
    Plots.plot!(trap_solution[:,1],trap_solution[:,2],markershape=:o, linetype=:scatter, label = "Trapezoidal")
    Plots.plot!(euler_solution[:,1],euler_solution[:,2],markershape=:o, linetype=:scatter, label = "Euler")
    Plots.plot!(rk4o_solution[:,1],rk4o_solution[:,2],markershape=:d, linetype=:scatter,label = "RK4")
    title!("Solutions for f(t) = 1 - 0.5e^t + t^2")
    ylabel!("Y")
    xlabel!("Time")
    #
    savefig("plotOdeMethodComparison.png")
end

one_ode()