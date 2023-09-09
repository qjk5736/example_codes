%
% Copyright (c) 2022 John I. Krassikoff
%
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so, subject to the following conditions:
%
% The above copyright notice and this permission notice shall be included in all
% copies or substantial portions of the Software.
%
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
% SOFTWARE.
%  
%   A simple script that calculates first order derivatives of a 
%   continuous function. The derivative is evaluated using four
%   different schemes; forward, backward, central and Richardson.
%   The error of the four methods relative to the analytical result 
%   is plotted. A table of maximum and minimum values is displayed 
%   in the commmand  window.
%
function first_order_derivatives()
close all; clear variables;
% Functions
f_x = @(x) (x.^2.*sin(x)-1/12.*x.^3);
f_x_prime = @(x)(x.^2.*cos(x) + 2.*x.*sin(x) - (3/12).*x.^2);
forward_derivative = @(f_x, x, h)((f_x(x+h)-f_x(x))/h);
backward_derivative = @(f_x, x,h)((f_x(x)-f_x(x-h))/h);
central_derivative = @(f_x, x,h)((f_x(x+h)-f_x(x-h))/(2*h));
richardson_derivative = @(f_x, x,h)(1/(12*h).*(f_x(x-2*h) ...
    - 8.*f_x(x-h) + 8.*f_x(x+h) - f_x(x+2*h))); 
% Constants and variables
h = 0.1;
x = linspace(-50, 50, 500);
% Calculate derivatives for each method
y = f_x_prime(x);
y1 = forward_derivative(f_x,x,h);
y2 = backward_derivative(f_x,x,h);
y3 = central_derivative(f_x,x,h);
y4 = richardson_derivative(f_x,x,h);
% Calculate the errors for each method.
forward_error = y1-y;
backward_error = y2-y;
central_error = y3-y; 
richardson_error = y4-y;
% Plot the errors for each method.
figure('Name', 'Derivative Error by Method', 'position',[400,400,900,600]); 
plot(x,forward_error,'cyan','linewidth',2);hold on
plot(x,backward_error,'r','linewidth',2)
plot(x,central_error,'g','linewidth',2)
plot(x,richardson_error,'b','linewidth',2)
hold off
xlabel('x')
ylabel("f'(x)")
box on
grid on
legend('forward','backward','central','Richardson', 'Location','South')
title("analytical f'(x) = x^2cos(x) + (2x)sin(x) - (3/12)x^2")
% Display a table of maximum and minimum values for each method.
error_cel = num2cell([0, min(forward_error), max(forward_error); ...
    0, min(backward_error), max(backward_error); ...
    0, min(central_error), max(central_error); ...
    0, min(richardson_error), max(richardson_error)]);
error_cel{1,1} = 'forward';
error_cel{2,1} = 'backward';
error_cel{3,1} = 'central';
error_cel{4,1} = 'Richardson';
error_table = cell2table(error_cel,...
    "VariableNames",["method" "min error" "max error"]);
disp(error_table);
end
