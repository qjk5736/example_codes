!
!   Copyright 2022 John I. Krassikoff
!   
!   This program is free software : you can redistribute it and /or modify
!   it under the terms of the GNU General Public License as published
!   by the Free Software Foundation, either version 3 of the License, or
!   (at your option) any later version.
!   
!   This program is distributed in the hope that it will be useful,
!   but WITHOUT ANY WARRANTY; without even the implied warranty of
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
!   GNU General Public License for more details.
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