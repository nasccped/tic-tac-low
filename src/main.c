/* ------------------------------------------------------------------
 *
 * main.c
 *
 *     file responsible for store the main task and / or the
 *     combination of all tasks
 * ----------------------------------------------------------------*/
#include <stdio.h>

int main(int argc, char *argv[]) {

  int number;

  do {

    printf("Insert a number [1 - 10]: ");

    scanf("%d", &number);

  } while (number > 10 || number < 1);



  return 0;
}
