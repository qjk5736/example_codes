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
module ModBubblesort

export bsort

function sort(y)
    println("This is bubblesort[x].")
    n_y = length(y)
    while (n_y > 0)
        n_next = 0
        j = 0
        for i = 2:n_y
            j = i - 1
            if (y[i] < y[j])
                temp = y[i]
                y[i] = y[j]
                y[j] = temp
                n_next = i
            end
        end
        n_y = n_next
    end
    return y
end

end
