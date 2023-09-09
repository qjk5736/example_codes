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