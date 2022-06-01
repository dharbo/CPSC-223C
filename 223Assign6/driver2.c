#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "customer_info.h"

void displaycustomer(struct customer_info person);
struct customer_info get_cust();

int main() {
  FILE* records = fopen("records.data", "r+b");
  const int max_records_num = 10;
  struct customer_info cust;
  char discard[1024];
  unsigned int acc_num;

  printf("sizeof(struct customer_info) = %lu\n", sizeof(struct customer_info));

  int counter = 0;

  printf("The random access file \"records.data\" contains the following records:\n");
  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && counter < max_records_num) {
    displaycustomer(cust);
    printf("\n");
    counter++;
    fread(&cust, sizeof(struct customer_info), 1, records);
  }

  int position;
  printf("Enter an integer between 0 and %d (inclusive): ", counter-1);
  scanf("%d", &position);
  fseek(records, position*sizeof(struct customer_info), SEEK_SET);
  fread(&cust, sizeof(struct customer_info), 1, records);
  printf("The customer record at this location is:\n");
  displaycustomer(cust);
  printf("\n");

  printf("Input data for new student record to be written to the end of the random access file\n");
  fgets(discard, 1024, stdin);
  cust = get_cust();
  if (strlen(cust.name) > 0) {
    fseek(records, 0, SEEK_END);
    fwrite(&cust, sizeof(struct customer_info), 1, records);
    counter++;
    printf("A new record was written to the end of the file. There are now %d records in the file\n\n", counter);
  }

  printf("The updated random access file \"records.data\" contains the following records:\n");
  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && counter < max_records_num) {
    displaycustomer(cust);
    printf("\n");
    fread(&cust, sizeof(struct customer_info), 1, records);
  }
  printf("The number of customer records in the file records.data is now %d\n", counter);

  printf("Enter the account number of the customer to be searched: ");
  scanf("%ud", &acc_num);
  rewind(records);
  fread(&cust, sizeof(struct customer_info), 1, records);
  while (!feof(records) && cust.account_number != acc_num) {
    fread(&cust, sizeof(struct customer_info), 1, records);
  }
  if (cust.account_number == acc_num) {
    printf("The requested customer record has been found:\n");
    displaycustomer(cust);
  } else {
    printf("The requested customer record was NOT found:\n");
  }

  fclose(records);
  printf("The file \"records.data\" is now closed and saved in storage.\n");


  return 0;
}

void displaycustomer(struct customer_info person) {
  printf("Customer name: %s\n", person.name);
  printf("Customer account number: %u\n", person.account_number);
  printf("Customer credit availability: %lf\n", person.credit_available);
  printf("Customer balance due: %lf\n", person.balance_due);
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
