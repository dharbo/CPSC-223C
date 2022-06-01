//****************************************************************************************************************************
//Program name: "String Search".  This program demonstrates the process of searching for the location of a user              *
//inputted string from a user inputted file. Copyright (C) 2021 David Harboyan                                               *
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
//version 3 as published by the Free Software Foundation.                                                                    *
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         *
//warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
//A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
//****************************************************************************************************************************
//Author information
//  Author name: David Harboyan
//  Author email: harboyandavid@csu.fullerton.edu
//
//Program information
//  Program name: String Search
//  Programming languages: Three modules in C and one bash file
//  Date program began: 2022-Feb-22
//  Date of last update: 2022-Mar-02
//  Date of reorganization of comments: 2022-Mar-02
//  Date of clarification of terms within comments: 2022-Mar-02
//  Files in this program: search.c copyfile.c output_array.c r.sh
//  Status: There are no user inputs.  The program performs correctly.
//
//References for this program
//  Kernighan and Ritchie, The C Programming Language, Second Edition, Appendix B10.
//
//Purpose
//  Show how to search for the location of a user inputted string from a user inputted file.
//
//This file
//   File name: output_array.c
//   Language: C
//   Max page width: 132 columns
//   Compile: gcc -c -Wall -m64 -no-pie -o output_array.o output_array.c -std=gnu11 -lm
//   Link: gcc -m64 -no-pie -o run.out search.o copyfile.o output_array.o -std=gnu11 -lm
//   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
//
/******************************* Code starts here *********************************/

#include "stdio.h"
#include "string.h"

void output_array(int match_location[], int count);

void output_array(int match_location[], int count) {
  // Loop though the int array and print everything in it.
  for (int i = 0; i < count; ++i) {
    printf("%d\n", match_location[i]);
  }
}
