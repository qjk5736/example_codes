#
# Copyright (c) 2022 John I. Krassikoff
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
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
