# //****************************************************************************************************************************
# //Program name: "Manage Students".  This program demonstrates the process of storing struct information inputted by the user *
# //and sorts them according to some factor. Copyright (C) 2022 David Harboyan                                                 *
# //This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
# //version 3 as published by the Free Software Foundation.                                                                    *
# //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         *
# //warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
# //A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
# //****************************************************************************************************************************
# //Author information
# //  Author name: David Harboyan
# //  Author email: harboyandavid@csu.fullerton.edu
# //
# //Program information
# //  Program name: Manage Students
# //  Programming languages: Four modules in C, one header in C, and one bash file
# //  Date program began: 2022-Mar-10
# //  Date of last update: 2022-Apr-04
# //  Date of reorganization of comments: 2022-Apr-04
# //  Date of clarification of terms within comments: 2022-Apr-04
# //  Files in this program: driver.c fillarray.c output_array.c bubble_sort.c student.h r.sh
# //  Status: There are no user inputs.  The program performs correctly.
# //
# //References for this program
# //  Kernighan and Ritchie, The C Programming Language, Second Edition, Appendix B10.
# //
# //Purpose
# //  To store struct information inputted by the user and sort them according to some factor.
# //
# //This file
# //   File name: r.sh
# //   Language: bash
# //   Max page width: 132 columns
# //   Link: gcc -m64 -no-pie -o run.out driver.o fillarray.o output_array.o bubble_sort.o -std=gnu11 -lm
# //   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
# //
# /******************************* Code starts here *********************************/

#!/bin/bash

#Program: Management of Structs
#Author: David Harboyan

#Remove old files.
rm *.o
rm *.out

#Compile the C files.
gcc -c -Wall -m64 -no-pie -o driver.o driver.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o fillarray.o fillarray.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o output_array.o output_array.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o bubble_sort.o bubble_sort.c -std=gnu11 -lm


#Link the object files.
gcc -m64 -no-pie -o run.out driver.o fillarray.o output_array.o bubble_sort.o -std=gnu11 -lm

#Run the program.
./run.out

#Remove object files that have been used.
rm *.o
rm *.out
