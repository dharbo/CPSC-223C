#!/bin/bash

# // ; Author Contact:
# // ;   Name: David Harboyan
# // ;   Email: harboyandavid@csu.fullerton.edu

#Remove old files.
rm *.o
rm *.out

# #Compile the C files.
gcc -c -Wall -m64 -no-pie -o driver.o driver.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o bubble_sort.o bubble_sort.c -std=gnu11 -lm

gcc -c -Wall -m64 -no-pie -o prof_bubble_sort.o prof_bubble_sort.c -std=gnu11 -lm

#Link the object files.
gcc -m64 -no-pie -o run.out driver.o bubble_sort.o prof_bubble_sort.o -std=gnu11 -lm

#Run the program.
./run.out

#Remove object files that have been used.
rm *.o
rm *.out
