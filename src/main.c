/* ------------------------------------------------------------------
 *
 * main.c
 *
 *     file responsible for store the main task and / or the
 *     combination of all tasks
 * ----------------------------------------------------------------*/
#include <stdio.h>

// main function
int main(int argc, char *argv[]) {

  // initialize an empty int variable
  int number;

  /*
    FIXME: cool block of code. Some kind of question is done,
           you enter a int type value such as 10, 32, 54, etc...
           but, if you enter like a char `a`, some bug behaviours
           occurs
  */
  do {

    printf("Insert a number [1 - 10]: ");

    scanf("%d", &number);

  } while (number > 10 || number < 1);



  return 0;
}
