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
!   the module file.
!
! gfortran -Wall -Wextra -Wimplicit-interface -fcheck=all -fbacktrace 
! -fcoarray=single objects.f90 main.f90 -o test_mod.exe
!
module objects
  
    implicit none

    type, public :: Square
        real(8) :: height
        real(8) :: width
    contains
        procedure :: calculate_area => ca
    end type Square

    type, extends(Square) :: Cube
        real(8) :: depth
    contains
        procedure :: calculate_volume => cv
        procedure :: calculate_volume_internal => cvi
    end type Cube

contains

    subroutine ca(this)
        class(Square), intent(in) :: this
        print *, (this%height * this%width)
    end subroutine ca

    real(8) function cv(this, depth) result(Vol)
        class(Cube), intent(in) :: this
        real(8), intent(in) :: depth
        Vol = (this%height * this%width * depth )
    end function cv

    real(8) function cvi(this) result(Vol)
        class(Cube), intent(in) :: this
        Vol = (this%height * this%width * this%depth )
    end function cvi

end module objects