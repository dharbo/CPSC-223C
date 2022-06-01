#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

int main() {
  printf("Welcome to Right Triangles\n");
  printf("This software was built by and maintained by Systems Programmer David Harboyan.\n");

  time_t current_linux_time;
  current_linux_time = time(NULL);
  struct tm * broken = localtime(&current_linux_time);

  printf("Today is ");
  switch(broken->tm_mon) {
    case 0: printf("January");
            break;
    case 1: printf("February");
            break;
    case 2: printf("March");
            break;
    case 3: printf("April");
            break;
    case 4: printf("May");
            break;
    case 5: printf("June");
            break;
    case 6: printf("July");
            break;
    case 7: printf("August");
            break;
    case 8: printf("September");
            break;
    case 9: printf("October");
            break;
    case 10: printf("November");
            break;
    case 11: printf("December");
            break;
    default: printf("Unknown");
            break;
  }
  printf(" %02d, ", broken->tm_mday);
  printf("%4d at ", broken->tm_year+1900);

  if (broken->tm_hour > 12) {
    printf("%02d:%02dpm.\n", broken->tm_hour-12, broken->tm_min);
  //  printf("%02d pm.\n", broken->tm_min);
  } else {
    printf("%02d:%02dam.\n", broken->tm_hour, broken->tm_min);
  }


  printf("This program will manage all of your right triangles.\n");
  printf("Please enter the lengths of the two sides of the triangle forming a right angle. Put ws between\n");
  printf("the two inputs and press enter after the second number.\n");

  double length1, length2;
  scanf("%lf%lf", &length1, &length2);

  printf("You entered %lf and %lf.\n", length1, length2);

  if (length1 <= 0 || length2 <= 0) {
    printf("Invalid data are among the inputs. Please run this program again.\n");
  } else {
    double area = ((length1 * length2) * 0.5);
    printf("The area of this right triangle is %.03lf square units.\n", area);

    double perimeter = (length1 + length2 + sqrt((length1*length1) + (length2*length2)));
    printf("The perimeter of the same triangle is %lf linear units.\n", perimeter);
  }

  struct timespec *present = malloc(sizeof(struct timespec));
  long int nanosec = clock_gettime(CLOCK_REALTIME, present);
  printf("The time is now %ld%ld ns AE.\n", present->tv_sec, present->tv_nsec);

  printf("Have a nice day.\n");
  printf("An integer 0 will be sent to the operating system as a signal of successful execution. Bye.\n");


  return 0;
}
