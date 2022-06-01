//****************************************************************************************************************************
//Program name: "Tokenizer".  This program demonstrates the process of creating tokens from a file provided by the user.     *
//Copyright (C) 2021 David Harboyan                                                                                          *
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
//  Program name: Tokenizer
//  Programming languages: One module in C and one bash file
//  Date program began: 2022-Feb-07
//  Date of last update: 2022-Feb-16
//  Date of reorganization of comments: 2022-Feb-16
//  Date of clarification of terms within comments: 2022-Feb-16
//  Files in this program: driver2.c , r.sh , inputfile.txt
//  Status: There are no user inputs.  The program performs correctly.
//
//References for this program
//  Kernighan and Ritchie, The C Programming Language, Second Edition, Appendix B10.
//
//Purpose
//  Show how to create tokens from a file using separator provided by the user.
//
//This file
//   File name: driver2
//   Language: C
//   Max page width: 132 columns
//   Compile: gcc -c -Wall -m64 -no-pie -o run.o driver2.c -std=gnu11 -lm
//   Link: gcc -m64 -no-pie -o run.out run.o -std=gnu11 -lm
//   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
//
/******************************* Code starts here *********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  printf("Welcome to Epic Software Systems, Inc. Head of Systems Lab: David Harboyan\n");


  // Get the filename from the user.
  char* filename = (char*)malloc(4192*sizeof(char));
  printf("Enter the name of a file to be tokenized: ");
  fgets(filename, 4192, stdin);
  *(filename + strlen(filename) - 1) = '\0'; // Remove the \n character.

  // Open and read the file.
  FILE* specialdata = fopen(filename, "r");
  char* filearray = (char*)malloc(1000*sizeof(char));

  // Store the string from the file into filearray.
  int j = 0;
  int onebyte;
  while ((onebyte = fgetc(specialdata)) != EOF) {
    filearray[j] = onebyte;
    j++;
  }
  *(filearray + strlen(filearray) - 1) = '\0';  // Remove the \n character.
  printf("%s\n", filearray);
  printf("%ld characters were read from the file into an array of the program.\n", strlen(filearray) + 1);
  // The +1 is there b/c we removed the newline character beforehand.

  // Get the separators from the user.
  char* sep = (char*)malloc(100*sizeof(char));
  printf("The tokenizing is ready to begin.\n");
  printf("Enter the separator characters which may include white space and press enter: ");
  fgets(sep, 100, stdin);
  *(sep + strlen(sep) - 1) = '\0';
  printf("Confirmation: These are the separators => %s\n", sep);

  // Create the tokens and store them in tokenarray.
  int count = 0;
  char *tokenarray[100];
  while (strlen(filearray) > 0) {
    tokenarray[count] = strtok(filearray, sep);
    filearray = filearray + strlen(filearray) + 1;
    count++;
  }

  printf("Tokenizing has finished.\nHere is the complete list of tokens:\n");

  // Print the tokens.
  int currtok = 0;
  while (currtok < count) {
    printf("Token number %d is %s\n", currtok, tokenarray[currtok]);
    currtok++;
  }

  printf("\nTotal number of tokens is %d\n", count);
  printf("Have a nice evening.\n");

  return 0;
}
