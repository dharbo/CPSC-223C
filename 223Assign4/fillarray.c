//****************************************************************************************************************************
//Program name: "Manage Students".  This program demonstrates the process of storing struct information inputted by the user *
//and sorts them according to some factor. Copyright (C) 2022 David Harboyan                                                 *
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
//  Program name: Manage Students
//  Programming languages: Four modules in C, one header in C, and one bash file
//  Date program began: 2022-Mar-10
//  Date of last update: 2022-Apr-04
//  Date of reorganization of comments: 2022-Apr-04
//  Date of clarification of terms within comments: 2022-Apr-04
//  Files in this program: driver.c fillarray.c output_array.c bubble_sort.c student.h r.sh
//  Status: There are no user inputs.  The program performs correctly.
//
//References for this program
//  Kernighan and Ritchie, The C Programming Language, Second Edition, Appendix B10.
//
//Purpose
//  To store struct information inputted by the user and sort them according to some factor.
//
//This file
//   File name: fillarray.c
//   Language: C
//   Max page width: 132 columns
//   Compile: gcc -c -Wall -m64 -no-pie -o fillarray.o fillarray.c -std=gnu11 -lm
//   Link: gcc -m64 -no-pie -o run.out driver.o fillarray.o output_array.o bubble_sort.o -std=gnu11 -lm
//   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
//
/******************************* Code starts here *********************************/


#include "stdio.h"
#include "student.h"
#include "stdlib.h"
#include "string.h"

int fillarray(struct student* list[], int size);

int fillarray(struct student* list[], int size) {
    int index = 0;
    int stop = 0;
    char* fstop;
    list[index] = (struct student*)malloc(1*sizeof(struct student));


    printf("Please press ctrl+D anytime when you are done inputting data.\n\n");

    printf("Name: ");
  //  stop = scanf("%s", list[index]->name);
    fstop = fgets(list[index]->name, 25, stdin);
    *(list[index]->name + strlen(list[index]->name) - 1) = '\0'; // Remove the \n character.

    while (index < size && stop != EOF && fstop != NULL) {

      printf("CWID: ");
      stop = scanf("%d", &list[index]->cwid);
      getchar(); // Get rid of "\n" in the buffer.

      printf("Major: ");
      // stop = scanf("%s", list[index]->major);
      fstop = fgets(list[index]->major, 25, stdin);
      *(list[index]->major + strlen(list[index]->major) - 1) = '\0'; // Remove the \n character.

      printf("Class level (fresh=0, soph=1, junior=2, senior=3): ");
      stop = scanf("%ud", &list[index]->level);

      printf("Zip: ");
      stop = scanf("%d", &list[index]->zip);

      printf("\n");

      index++;
      if(index < size) {
        getchar(); // Get rid of "\n" in the buffer.
        list[index] = (struct student*)malloc(1*sizeof(struct student));
        printf("Name: ");
        //stop = scanf("%s", list[index]->name);
        fstop = fgets(list[index]->name, 25, stdin);
        *(list[index]->name + strlen(list[index]->name) - 1) = '\0'; // Remove the \n character.
      }

     }
     return index;
}
