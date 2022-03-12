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
module ModSelectionsort

export sort

function sort(y)
    println("This is selectionsort[x].")
    n_y = length(y);
    for j = 1:(n_y - 1)
        min = j;
        for i = (j + 1):n_y
            if (y[i] < y[min])
                min = i;
            end
        end
        if (min != j)
            temp = y[min];
            y[min] = y[j];
            y[j] = temp;
        end
    end
    return y
end 

end
