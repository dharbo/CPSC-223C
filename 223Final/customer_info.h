// ; Author Contact:
// ;   Name: David Harboyan
// ;   Email: harboyandavid@csu.fullerton.edu
// ;   Course: CPSC 223C
// ;   "Final exam program May 16, 2022."

#ifndef customer_info_h
#define customer_info_h

struct customer_info
{
  unsigned int account_number;
  char name[25];
  double credit_available;
  double balance_due;
};

#endif /*customer_info_h*/
