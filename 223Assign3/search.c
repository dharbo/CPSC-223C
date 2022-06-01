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
//   File name: search.c
//   Language: C
//   Max page width: 132 columns
//   Compile: gcc -c -Wall -m64 -no-pie -o search.o search.c -std=gnu11 -lm
//   Link: gcc -m64 -no-pie -o run.out search.o copyfile.o output_array.o -std=gnu11 -lm
//   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
//
/******************************* Code starts here *********************************/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern int copyfile(char*, char*, int);
extern void output_array(int [], int);

int main() {

  // Welcome prompts.
  printf("Welcome to Find Your Match produced by Orange Blossom Lucky Software, Inc.\n");
  printf("Project leader: David Harboyan\n");
  printf("This program will find the matching strings in any file.\n\n");

  // Get the filename from the user.
  char* filename = (char*)malloc(4192*sizeof(char));
  printf("Please enter the name of the file to be searched: ");
  fgets(filename, 1024, stdin);
  *(filename + strlen(filename) - 1) = '\0'; // Remove the \n character.
  printf("Thank you. You entered %s\n\n", filename);

  // Call the copyfile function to get the contents of the file.
  char* dataarray = (char*)malloc(4192*sizeof(char));
  int counter = copyfile(filename, dataarray, 4192);

  // Get the string to be searched from the user.
  char* search_string = (char*)malloc(1024*sizeof(char));
  printf("Please enter the search pattern you are seeking: ");
  fgets(search_string, 1024, stdin);
  *(search_string + strlen(search_string) - 1) = '\0'; // Remove the \n character.
  printf("Thank you. You entered %s\n\n", search_string);

  // Create a pointer to the string and create an integer array to hold locations.
  char* p = dataarray;
  int int_array[500];
  counter = 0;

  // Loop until all the search_string instances are found, then break out.
  while (strlen(p) > 0) {
      p = strstr(p, search_string);
      if (p != NULL) {
        int_array[counter] = (int)(p - dataarray);
        p = p + 1;
        counter++;
      } else {
        break;
      }
  }

  // Call output_array to print the locations from int_array.
  printf("The search has completed. The search key %s is found in these positions within the file:\n", search_string);
  output_array(int_array, counter);

  // Farwell prompt.
  printf("\nThat completes the string search. Please enjoy your matches.\n");
  printf("A zero will be returned to the operating system.\nBye.\n");

  return 0;
}
