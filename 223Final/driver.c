// ; Author Contact:
// ;   Name: David Harboyan
// ;   Email: harboyandavid@csu.fullerton.edu
// ;   Course: CPSC 223C
// ;   "Final exam program May 16, 2022."

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "customer_info.h"

int append_file(const int);
int show_list(const int);
int show_database_nums(const int);
void use_position(int);
void update(int);


int main() {

  printf("Welcome to Morning Glory Credit Lender, LLC\n");
  printf("CEO: David Harboyan\n\n");

  const int max_records_num = 10;
  int counter = show_database_nums(max_records_num);  // initialize counter with the number of accounts

  printf("Here are your options:\n");
  printf("     A: Append a new customer.\n");
  printf("     L: Show all customers.\n");
  printf("     R: Show one customer by giving its position.\n");
  printf("     U: Given the position of the customer, update it.\n");
  printf("     Q: Exit this program.\n");

  // Get user's selection.
  printf("\nPlease select an option: ");
  char selection;
  selection = getchar();
  char discardarray[1024];
  fgets(discardarray, 1024, stdin);  // clear buffer
  // Loop through user selections.
  while(toupper(selection) != 'Q') {
    switch(toupper(selection)) {
      case 'A': case 'a':
            counter = append_file(max_records_num);
            break;
      case 'L': case 'l':
            counter = show_list(max_records_num);
            break;
      case 'R': case 'r':
            use_position(counter);
            break;
      case 'U': case 'u':
            update(counter);
            break;
      default:
            printf("Error in input. Try again.\n");
            break;

    }
    // Get user's next selection.
    printf("\nPlease enter your choice: ");
    selection = getchar();
    fgets(discardarray, 1024, stdin); // clear buffer
  }

  // Farewell message.
  printf("\nThe binary file morningglory.bin was saved for future use.\n");
  printf("Have a great day.\n");

  return 0;
}

// Display a customer's info.
void displaycustomer(struct customer_info person) {
  printf("\nCustomer name: %s\n", person.name);
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

  // Get the rest of the customer info.
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

// Add a customer to an existing morningglory.bin file.
int append_file(const int max) {
  FILE* records = fopen("morningglory.bin", "a+b");
  struct customer_info cust;

  // Add to the file
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
  FILE* records = fopen("morningglory.bin", "r+b");
  struct customer_info cust;
  int counter = 0;

  // Print out all the structs from the binary file.
  printf("The random access file \"morningglory.bin\" contains the following records:\n");
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
  FILE* records = fopen("morningglory.bin", "r+b");
  struct customer_info cust;
  int counter = 0;

  // Read through the structs and keep a count.
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
  FILE* records = fopen("morningglory.bin", "r+b");
  struct customer_info cust;
  int position;

  // Get the position.
  printf("Enter a position between 0 and %d (inclusive): ", counter-1);
  scanf("%d", &position);

  if (position > counter-1 || position < 0) {
    printf("Invalid position!\n");
    char discardarray[1024];
    fgets(discardarray, 1024, stdin);
    return;
  }

  fseek(records, position*sizeof(struct customer_info), SEEK_SET);
  fread(&cust, sizeof(struct customer_info), 1, records);

  // Print the struct at the position.
  printf("The customer record at this location is:\n");
  displaycustomer(cust);
  printf("\n");
  char discardarray[1024];
  fgets(discardarray, 1024, stdin);    // clear buffer

  fclose(records);
}

// Update a struct at a position given by the user.
void update(int counter) {
  FILE* records = fopen("morningglory.bin", "r+b");
  rewind(records);
  struct customer_info person;
  int position;

  // Get the position.
  printf("Enter the position of the customer, between 0 and %d (inclusive): ", counter-1);
  scanf("%d", &position);

  printf("\nEnter new data below:\n");
  char discard[1024];
  fgets(discard, 1024, stdin);

  if (position > counter-1 || position < 0) {
    printf("Invalid position!\n");
    char discardarray[1024];
    fgets(discardarray, 1024, stdin);
    return;
  }

  fseek(records, position*sizeof(struct customer_info), SEEK_SET);

  // Get the new data.
  printf("Enter customer name: ");
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

  // Write to the file at the correct position.
  fwrite(&person, sizeof(struct customer_info), 1, records);

  printf("The customer data in position %d were updated.\n\n", position);
  fclose(records);
}
