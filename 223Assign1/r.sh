#!/bin/bash

#Remove old files.
rm *.o
rm *.out

#Compile
gcc -c -Wall -m64 -no-pie -o run.o Hello.c -std=gnu11 -lm#-std=c17

#Link the object files.
gcc -m64 -no-pie -o run.out run.o -std=gnu11 -lm #-std=c17

#Run the program.
./run.out
