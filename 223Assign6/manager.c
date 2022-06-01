#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "customer_info.h"

void displaycustomer(struct customer_info person);
struct customer_info get_cust();

int append_file(const int);
int show_list(const int);
int show_database_nums(const int);
void use_position(int counter);
void use_account();
//int overwrite();
//int create();

int main() {

  printf("Welcome to Sunflower Lenders, Inc.\n");
  printf("We provide the money you need.\nHere is our menu:\n");

  printf("     A: Append new customer.\n");
  printf("     L: Show a list of all accounts.\n");
  printf("     S: Show the number of customers in the database.\n");
  printf("     F: Given the account # find the position of the customer with that number.\n");
  printf("     R: Given the position number display the data of the account stored there.\n");
  //printf("     O: Create/Overwrite the records.data file and add its first new customer.\n");
  //printf("     C: Create a records.data file, if one does not exist and add its first new customer.\n");
  printf("     Q: Exit from this program.\n");

  // Get user's selection.
  printf("\nPlease enter a request: ");
  char selection;
  selection = getchar();
  char discardarray[1024];
  fgets(discardarray, 1024, stdin);  // clear buffer

  const int max_records_num = 10;
  int counter = show_database_nums(max_records_num);  // initialize counter with the number of accounts

  while(toupper(selection) != 'Q') {
    switch(toupper(selection)) {

      case 'A': case 'a':
            counter = append_file(max_records_num);
            break;
      case 'L': case 'l':
            counter = show_list(max_records_num);
            break;
      case 'S': case 's':
            counter = show_database_nums(max_records_num);
            printf("The number of accounts in the database is %d.\n", counter);
            break;
      case 'F': case 'f':
            use_account();
            break;
      case 'R': case 'r':
            use_position(counter);
            break;
      // case 'O': case 'o':
      //       counter = overwrite();
      //       break;
      // case 'C': case 'c':
      //       counter = create();
      //       break;
      default:
            printf("Error in input. Try again.\n");
            break;

    }
    // Get user's next selection.
    printf("\nPlease enter your choice: ");
    selection = getchar();
    fgets(discardarray, 1024, stdin); // clear buffer
  }

  printf("\nThank you for using this program. Bye!\n");

  return 0;
}

// Display a customer's info.
void displaycustomer(struct customer_info person) {
  printf("Customer name: %s\n", person.name);
  printf("Customer account number: %u\n", person.account_number);
  printf("Customer credit availability: %.2lf\n", person.credit_available);
  printf("Customer balance due: %.2lf\n", person.balance_due);
}

// Find a customer and return it as a struct with all it's info.
struct customer_info get_cust() {
  struct customer_info person;
  printf("Enter customer name or <enter> to terminate inputs: ");
  fgets(person.name, 25, stdin);
  person.name[strlen(person.name)-1] = '\0';

  if (strlen(person.name) > 0) {
    printf("Enter account number: ");
    scanf("%u", &person.account_number);
    printf("Enter credit available: ");
    scanf("%lf", &person.credit_available);
    printf("Enter balance due: ");
    scanf("%lf", &person.balance_due);
    char discard[1024];
    fgets(discard, 1024, stdin); // clear buffer
  }
  return person;
}

// Add a customer to an existing records.data file.
int append_file(const int max) {
  FILE* records = fopen("records.data", "a+b");
  struct customer_info cust;

  int counter = 0;
  cust = get_cust();
  while (counter < max && strlen(cust.name) > 0) {
    fwrite(&cust, sizeof(struct customer_info), 1, records);
    counter++;
    cust = get_cust();
  }
  fclose(records);

  return counter;
}

// Show all the customers and their data.
int show_list(const int max) {
  FILE* records = fopen("records.data", "r+b");
  struct customer_info cust;
  int counter = 0;

  printf("The random access file \"records.data\" contains the following records:\n");
  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && counter < max) {
    displaycustomer(cust);
    printf("\n");
    counter++;
    fread(&cust, sizeof(struct customer_info), 1, records);
  }

  fclose(records);

  return counter;
}

// Return the number of accounts that are in records.data.
int show_database_nums(const int max) {
  FILE* records = fopen("records.data", "r+b");
  struct customer_info cust;
  int counter = 0;

  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && counter < max) {
    counter++;
    fread(&cust, sizeof(struct customer_info), 1, records);
  }

  fclose(records);

  return counter;
}

// Find and display a customer given a position.
void use_position(int counter) {
  FILE* records = fopen("records.data", "r+b");
  struct customer_info cust;
  int position;

  printf("Enter an integer between 0 and %d (inclusive): ", counter-1);
  scanf("%d", &position);
  if (position > counter-1 || position < 0) {
    printf("Invalid position!\n");
    char discardarray[1024];
    fgets(discardarray, 1024, stdin);
    return;
  }
  fseek(records, position*sizeof(struct customer_info), SEEK_SET);
  fread(&cust, sizeof(struct customer_info), 1, records);
  printf("The customer record at this location is:\n");
  displaycustomer(cust);
  printf("\n");
  char discardarray[1024];
  fgets(discardarray, 1024, stdin);

  fclose(records);
}

// Find the position of a customer using their account number.
void use_account() {
  FILE* records = fopen("records.data", "r+b");
  struct customer_info cust;
  unsigned int acc_num;
  int position = 0;

  printf("Enter the account number of the customer to be searched: ");
  scanf("%ud", &acc_num);
  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && cust.account_number != acc_num) {
    fread(&cust, sizeof(struct customer_info), 1, records);
    position++;
  }
  if (cust.account_number == acc_num) {
    printf("The requested customer record has been found at position %d:\n", position);
    //displaycustomer(cust);
  } else {
    printf("The requested customer record was NOT found:\n");
  }
  char discardarray[1024];
  fgets(discardarray, 1024, stdin);

  fclose(records);
}
//
// int overwrite() {
//   FILE* records = fopen("records.data", "wb");
//   struct customer_info cust;
//
//   int counter = 0;
//   cust = get_cust();
//   if (strlen(cust.name) > 0) {
//     fwrite(&cust, sizeof(struct customer_info), 1, records);
//     counter++;
//   }
//
//   fclose(records);
//
//   return counter;
//
// }
//
// int create() {
//   FILE* records = fopen("records.data", "wb");
//   struct customer_info cust;
//
//   int counter = 0;
//   cust = get_cust();
//   if (strlen(cust.name) > 0) {
//     fwrite(&cust, sizeof(struct customer_info), 1, records);
//     counter++;
//   }
//
//   fclose(records);
//
//   return counter;
// }
