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