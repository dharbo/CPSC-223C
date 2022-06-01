#!/bin/bash

#Remove old files.
rm *.o
rm *.out

#Compile
gcc -c -Wall -m64 -no-pie -o run.o driver2.c -std=gnu11 -lm

#Link the object files.
gcc -m64 -no-pie -o run.out run.o -std=gnu11 -lm

#Run the program.
./run.out
