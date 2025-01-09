#ifndef _STDIO_H
#include <stdio.h>
#endif

#include "./headers/utils.h"
#include "./headers/visuals.h"

int main(int argc, char *argv[]) {

  clear_terminal();
  printf("\n");

  printf("  Welcome to our positive/negative questions!\n");
  printf("  Answer this with an yes/no:\n");
  printf("  > ");

  int answer = yes_or_no_input();

  printf("\n");

  printf("  Your answer value is: ");

  switch (answer) {

  case 1:
    printf("\x1b[1;32mtrue");
    break;

  case 0:
    printf("\x1b[1;31mfalse");
    break;

  default:
    printf("\x1b[1;33minvalid");
  }

  printf("\x1b[0m\n\n");

  return 0;
}
