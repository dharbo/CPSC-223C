#!/bin/bash

#Author: David Harboyan

#Remove old files.
rm *.o
rm *.out

#Compile the C files.
gcc -c -Wall -m64 -no-pie -o driver2.o driver2.c -std=gnu11 -lm

#Link the object files.
gcc -m64 -no-pie -o run2.out driver2.o -std=gnu11 -lm

#Run the program.
./run2.out

#Remove object files that have been used.
rm *.o
rm *.out
