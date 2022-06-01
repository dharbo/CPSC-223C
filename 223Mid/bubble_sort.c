// ; Author Contact:
// ;   Name: David Harboyan
// ;   Email: harboyandavid@csu.fullerton.edu

#include "stdio.h"
#include "stdlib.h"

extern void bubble_sort(char* array2[], int size);

extern void bubble_sort(char* array2[], int size) {

    char* temp;

    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size-1-i; ++j) {
        if (*array2[j] > *array2[j+1]) {
          temp = array2[j];
          array2[j] = array2[j+1];
          array2[j+1] = temp;
        }
      }
    }
}
