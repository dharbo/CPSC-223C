#!/bin/bash

#Program: String Search
#Author: David Harboyan

#Remove old files.
rm *.o
rm *.out

#Compile the C files.
gcc -c -Wall -m64 -no-pie -o search.o search.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o copyfile.o copyfile.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o output_array.o output_array.c -std=gnu11 -lm

#Link the object files.
gcc -m64 -no-pie -o run.out search.o copyfile.o output_array.o -std=gnu11 -lm

#Run the program.
./run.out

#Remove object files that have been used.
rm *.o
rm *.out
