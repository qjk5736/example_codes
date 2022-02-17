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
!   A simple program showing solution of 3 simultaneous
!   equations by Gauss-Jordan elimination.
!
!   gfortran GaussJordanTest.f90 -o fortGaussJordan.exe
!
module testArrayMod   
    real,dimension(:,:),allocatable :: testarray    
end module testArrayMod
!
program Gauss_Jordan
use testArrayMod
implicit none
! constants
integer, parameter :: N = 3
! interface
interface
    subroutine perform_gje(N, array)
        integer :: N
        real, dimension(:,:), allocatable :: array 
    end subroutine perform_gje
end interface
! declare
integer :: l
! allocate
allocate(testarray(N,N+1))
! initialize
testarray = reshape((/3, 0, 3, 0, 4, 2, 2, 4, 5, 3, 4, 2/), shape(testarray))
! call the function
call perform_gje(N, testarray)
! print the calculated result
do l = 1,N
    print '(3x,"b("i1") = ",f7.4)', l, testarray(l,N+1)
end do
end program Gauss_Jordan

subroutine perform_gje(N, array)
    implicit none
    integer :: N
    real, dimension(:,:), allocatable :: array
    real :: pivot_element, scale
    integer :: i, j, k
    pivot_element = 1
    scale = 1
    i = 1
    j = 1
    k = 1
    ! begin
    do k = 1,N
        ! calculate the normalization
        pivot_element = array(k,k)
        do j = k,(N+1)
            array(k,j)=array(k,j)/pivot_element
        end do
        ! loop through the elimination
        do i = 1,N
            if(i .ne. k) then
                scale=array(i,k)
                do j = k,(N+1)
                    array(i,j)=array(i,j)-array(k,j)*scale
                end do
            end if
        end do
    end do
end subroutine perform_gje
