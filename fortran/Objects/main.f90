!
! Copyright (c) 2022 John I. Krassikoff
!
! Permission is hereby granted, free of charge, to any person obtaining a copy
! of this software and associated documentation files (the "Software"), to deal
! in the Software without restriction, including without limitation the rights
! to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
! copies of the Software, and to permit persons to whom the Software is
! furnished to do so, subject to the following conditions:
!
! The above copyright notice and this permission notice shall be included in all
! copies or substantial portions of the Software.
!
! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
! SOFTWARE.
!  
!   A simple program showing a little OOP capability. This is
!   the driver file.
!
! gfortran -Wall -Wextra -Wimplicit-interface -fcheck=all -fbacktrace 
! -fcoarray=single objects.f90 main.f90 -o test_mod.exe
!
program main

use objects

implicit none

real(8) :: x, y, z1, z2
type(Square) :: squar
type(Cube) :: cub

x = 3
y = 2
z1 = 4
z2 = 10

squar = Square(x, y)
cub = Cube(x, y, z1)
! Show that variable are set correctly.
print *, squar%height, squar%width
print *, cub%height, cub%width, cub%depth
! Show that inheritance works.
call squar%calculate_area()
call cub%calculate_area()
! Show that volume can be calculated differently.
print *, cub%calculate_volume_internal()
print *, cub%calculate_volume(z2)

end program main