%
%   Copyright 2022 John I. Krassikoff
%   
%   This program is free software : you can redistribute it and /or modify
%   it under the terms of the GNU General Public License as published
%   by the Free Software Foundation, either version 3 of the License, or
%   (at your option) any later version.
%   
%   This program is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
%   GNU General Public License for more details.
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
