// ; Author Contact:
// ;   Name: David Harboyan
// ;   Email: harboyandavid@csu.fullerton.edu

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern void bubble_sort(char* [], int);
extern void prof_bubble_sort(char* [], char* [], int);

int main() {

  /*Beginner*/

  printf("\nWelcome to the Beginner level!\n\n");

  // Get the filename from the user.
  char* filename = (char*)malloc(4192*sizeof(char));
  printf("Please enter the name of a file: ");
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
  printf("Here is a 1D array of the file's content:\n%s\n", filearray);
  printf("%ld characters were read from the file into an array of the program.\n", strlen(filearray) + 1);

  /*Academic*/

  printf("\nWelcome to the Academic level!\n\n");

  // Create tokens with the separator being a newline and store them into the 2D tokenarray.
  int count = 0;
  char* tokenarray[100];
  while (strlen(filearray) > 0) {
    tokenarray[count] = strtok(filearray, "\n");
    filearray = filearray + strlen(filearray) + 1;
    count++;
  }

  // Print the 2D array.
  printf("Here is a 2D array of the file's content:\n");
  int currtok = 0;
  while (currtok < count) {
    printf("row%d -> %s\n", currtok, tokenarray[currtok]);
    currtok++;
  }

  /*Universe*/

  printf("\nWelcome to the Universe level!\n");

  // Sort the 2D array.
  bubble_sort(tokenarray, count);

  // Print the sorted 2D array.
  printf("\nHere is the sorted 2D array:\n");
  currtok = 0;
  while (currtok < count) {
    printf("row%d -> %s\n", currtok, tokenarray[currtok]);
    currtok++;
  }

  /*Professional*/

  printf("\nWelcome to the Professional level!\n\n");

  printf("The sort keys are:\n");

  // Find the prices of each item and store it in price_array.
  char* price_array[100];
  currtok = 0;
  while (currtok < count) {
    char* p = tokenarray[currtok];
    int position = strlen(tokenarray[currtok]) - 4;
    p = p + position;
    printf("%s\n", p);
    price_array[currtok] = p;
    currtok++;
  }

  // Sort the array.
  prof_bubble_sort(tokenarray, price_array, count);

  // Print the sorted 2D array.
  printf("\nHere is a 2D array sorted by price:\n");
  currtok = 0;
  while (currtok < count) {
    printf("row%d -> %s\n", currtok, tokenarray[currtok]);
    currtok++;
  }

  // Write to a file.
  FILE* fp = fopen("food.sort", "w");
  currtok = 0;
  while (currtok < count) {
    fprintf(fp, "%s\n", tokenarray[currtok]);
    currtok++;
  }

  // Close files.
  fclose(specialdata);
  fclose(fp);

  printf("\nThank you for your time, have a nice day. Goodbye.\n");
  return 0;
}
