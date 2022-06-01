//****************************************************************************************************************************
//Program name: "Shopping Cart".  This program demonstrates the process of a user buying items from a file.                  *
//Copyright (C) 2022 David Harboyan                                                                                          *
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
//  Program name: Shopping Cart
//  Programming languages: One module in C and one bash file
//  Date program began: 2022-Apr-15
//  Date of last update: 2022-Apr-27
//  Date of reorganization of comments: 2022-Apr-27
//  Date of clarification of terms within comments: 2022-Apr-27
//  Files in this program: driver.c run.sh
//  Status: There are no user inputs.  The program performs correctly.
//
//References for this program
//  Kernighan and Ritchie, The C Programming Language, Second Edition, Appendix B10.
//
//Purpose
//  Customers can pick a file and choose items to buy. A receipt file generates when they exit.
//
//This file
//   File name: driver.c
//   Language: C
//   Max page width: 132 columns
//   Compile: gcc -c -Wall -m64 -no-pie -o driver.o driver.c -std=gnu11 -lm
//   Link: gcc -m64 -no-pie -o run.out driver.o -std=gnu11 -lm
//   Optimal print specification: 132 columns width, 7 points, monospace, 8½x11 paper
//
/******************************* Code starts here *********************************/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

void menu();
void show_inventory(char*);
void purchase_item(char*, FILE*);
void initialize_new_customer(FILE*, char*, int);
void prepare_receipt(FILE*, char*);
void view_cart(char*);

int main() {

  printf("Welcome to Golden State Emporium.\n\n");

  char selection = '0';
  char discardarray[1024];

  // First customer initialization.
  int customer_counter = 1;
  FILE* receiptfile;
  char receiptfilename[128];
  sprintf(receiptfilename, "receipt%d.txt", customer_counter);
  receiptfile = fopen(receiptfilename, "w");

  // Get the name of the inventory file.
  char inventoryname[64];
  printf("Enter the name of the inventory file: ");
  fgets(inventoryname, 64, stdin);
  inventoryname[strlen(inventoryname) - 1] = '\0';

  menu();

  // Get the choice from the user.
  printf("Please enter your choice: ");
  selection = getchar();
  fgets(discardarray, 1024, stdin);

  // Loop until user wants to exit.
  while(toupper(selection) != 'X') {
    switch (toupper(selection)) {
      case 'M': case 'm':
                menu();
                break;
      case 'I': case 'i':
                show_inventory(inventoryname);
                break;
      case 'P': case 'p':
                purchase_item(inventoryname, receiptfile);
                break;
      case 'V': case 'v':
                fclose(receiptfile);
                view_cart(receiptfilename);
                receiptfile = fopen(receiptfilename, "a");
                break;
      case 'X': case 'x':
                fclose(receiptfile);
                selection = 'X';
                break;
      default:
                printf("Error in input. Try again.\n");
                break;
    }
    printf("\nPlease enter your choice: ");
    selection = getchar();
    fgets(discardarray, 1024, stdin); // clear buffer
  }

  printf("Your receipt is in the file \"receipt.txt\".\n\n");

  // Get the receipt ready with the user's picked items.
  prepare_receipt(receiptfile, receiptfilename);

  fclose(receiptfile);

  printf("Thank you for using this program!\n");

  // Get rid of our cart file.
  remove(receiptfilename);

  return 0;
}

void menu() {
  printf("M = Show this menu\n");
  printf("I = Show itmes in stock\n");
  printf("P = Purchase an item\n");
  printf("V = View shopping cart\n");
  printf("X = Exit, compute amount due, generate receipt\n\n");
}

void show_inventory(char* inventoryname) {
  FILE* items = fopen(inventoryname, "r");
  char line[1024];
  while(fgets(line, 1024, items) != NULL) {
    fputs(line, stdout);
  }
  fclose(items);
}

void purchase_item(char* inventoryfilename, FILE* receiptfile) {
  printf("Please enter the name of the item to purchase: ");
  char item_wanted[1024];
  fgets(item_wanted, 1024, stdin);
  item_wanted[strlen(item_wanted) - 1] = '\0';

  FILE* items_in_stock = fopen(inventoryfilename, "r");
  char line[1024];
  int found = 0;

  while(!found && fgets(line, 1024, items_in_stock) != NULL) {
    if (strncmp(item_wanted, line, 4) == 0) {
      line[strlen(line) - 1] = '\0';
      printf("Item in stock: %s\n", line);
      found = 1;
    }
  }
  if (found) {
    fputs(line, receiptfile);
    fputc('\n', receiptfile);
  } else {
    printf("Item is out of stock or not in inventory.\n");
  }
}

void view_cart(char* receipts) {
  FILE* rec_file = fopen(receipts, "r");
  char line[1024];
  while (fgets(line, 1024, rec_file) != NULL) {
    fputs(line, stdout);
  }
  fclose(rec_file);
}

void prepare_receipt(FILE* receiptfile, char* receiptfilename) {
    FILE* checkout = fopen("receipt.txt", "w"); //maybe change mode

    receiptfile = fopen(receiptfilename, "r");

    // Print to the receipt.
    fprintf(checkout, "Golden State Emporium\nWe do our best to serve our customers\n\n");
    fprintf(checkout, "Today's purchases:\n\n   Item               Quantity      Cost\n");

    // Print the items to the receipt.
    char* filearray = (char*)malloc(1000*sizeof(char));
    int j = 0;
    int ch;
    while ((ch = fgetc(receiptfile)) != EOF) {
      fprintf(checkout, "%c", ch);
      filearray[j] = ch;
      j++;
    }
    *(filearray + strlen(filearray) - 1) = '\0';  // Remove the \n character.

    // Tokenize the contents and use strstr to find the '$' char. And add to the total.
    char* ptr;
    double total = 0.0;
    int count = 0;
    char* tokenarray[100];
    char* p = (char*)malloc(256*sizeof(char));
    char* price_array[100];
    while (strlen(filearray) > 0) {
      tokenarray[count] = strtok(filearray, "\n");
      filearray = filearray + strlen(filearray) + 1;
      p = strstr(tokenarray[count], "$");
      price_array[count] = p+1;
      total += strtod(price_array[count], &ptr);
      count++;
    }

    // Print to the receipt.
    fprintf(checkout, "\nAmount paid: $ %.2lf\n\nThank you for shopping at GSE.", total);
}
