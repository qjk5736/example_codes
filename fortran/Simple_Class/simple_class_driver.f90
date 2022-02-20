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
!   A driver for the simple class module.
!
! gfortran -Wall -Wextra -Wimplicit-interface -fcheck=all -fbacktrace 
! mod_simple_class.f90 simple_class_driver.f90 -o a.exe
!
program simple_class_driver
    use mod_simple_class, only : Star

    type(Star) :: star1
    type(Star) :: star2 = Star(name="Alpha Centauri", distance_ly=4.37, system_type = "triple")

    call star1 % dist_from_earth()
    call star2 % dist_from_earth()

end program simple_class_driver