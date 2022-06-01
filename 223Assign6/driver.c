#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "customer_info.h"

struct customer_info get_cust();

// //struct customer_info get_cust();
// struct student_info get_cust() {
//   struct customer_info person;
//   printf("Enter student name or cntl_d to indicate end of inputs: ");
//   fgets(person.name, 25, stdin);
//   person.name[strlen(person.name)-1] = '\0';
//   printf("Enter cwid: ");
//   scanf("%ud", &person.account_number);
//
//   return person;
// }

int main() {

  //char selection = '0';
  FILE* records = fopen("records.data", "wb");
  const int max_records_num = 10;
  struct customer_info cust;

  printf("Number of bytes in each customer record = %lu\n", sizeof(struct customer_info));
  printf("Max number of customer records permitted to be written to the file = %d\n", max_records_num);

  int counter = 0;

  cust = get_cust();
  while (counter < max_records_num && strlen(cust.name) > 0) {
    fwrite(&cust, sizeof(struct customer_info), 1, records);
    counter++;
    cust = get_cust();
  }

  fclose(records);
  printf("%d customer records have been written to the random access file. Goodbye!\n", counter);

  // printf("Welcome to Sunflower Lenders, Inc.\n");
  // printf("We provide the money you need.\nHere is our menu:\n");
  //
  // printf("     A: Append new customer.\n");
  // printf("     L: Show a list of all accounts.\n");
  // printf("     S: Show the number of customers in the database.\n");
  // printf("     F: Given the account # find the position of the customer with that number.\n");
  // printf("     R: Given the position number display the data of the account stored there.\n");
  // printf("     Q: Exit from this program.\n");
  //
  // printf("\nPlease enter a request: ");
  // selection = getchar();
  // fgets(discardarray, 1024, stdin);
  //
  // while(toupper(selection) != 'E') {
  //   switch(toupper(selection)) {
  //
  //     case 'A': case 'a':
  //
  //
  //
  //
  //     default:
  //             printf("Error in input. Try again.\n");
  //             break;
  //   }
  //   printf("\nPlease enter your choice: ");
  //   selection = getchar();
  //   fgets(discardarray, 1024, stdin); // clear buffer
  // }





  return 0;
}

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
