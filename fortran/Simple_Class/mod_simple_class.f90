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
!   A simple Fortran type(class) implementation in a module.
!
! gfortran -Wall -Wextra -Wimplicit-interface -fcheck=all -fbacktrace 
! mod_simple_class.f90 simple_class_driver.f90 -o a.exe
!
module mod_simple_class
    implicit none

    type :: Star
        character(len=15) :: name  = "Sol (the Sun)"
        real(4) :: distance_ly = 1.59e-5
        character(len=6) :: system_type = "single"
    contains
        procedure, pass(self) :: dist_from_earth
    end type Star
contains
    subroutine dist_from_earth(self)
        class(Star),intent(in) :: self
        print *, "The ", self % system_type, " star system ", self % name, &
             " is approximately  ", self % distance_ly,  &
             " light-years distant from the Earth.";
    end subroutine dist_from_earth

end module mod_simple_class