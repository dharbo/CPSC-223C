// ; Author Contact:
// ;   Name: David Harboyan
// ;   Email: harboyandavid@csu.fullerton.edu

#include "stdio.h"
#include "stdlib.h"

extern void prof_bubble_sort(char* array2[], char* price_array[], int size);

extern void prof_bubble_sort(char* array2[], char* price_array[], int size) {

    char* temp;
    char* temp2;

    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size-i-1; ++j) {
        if (*price_array[j] > *price_array[j+1]) {
          temp = array2[j];
          array2[j] = array2[j+1];
          array2[j+1] = temp;

          temp2 = price_array[j];
          price_array[j] = price_array[j+1];
          price_array[j+1] = temp2;
        }
      }
    }
}
