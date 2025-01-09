#ifndef _STDIO_H
#include <stdio.h>
#endif

#include "./headers/utils.h"
#include "./headers/visuals.h"

unsigned ENABLE_COLORS;

int main(int argc, char *argv[]) {

  clear_terminal();

  printf("\n");

  printf("  Enable ANSI basic colors? ( yes / no )\n");
  printf("  > ");

  int sec;
  ENABLE_COLORS = ((sec = yes_or_no_input()) == -1) ? 0 : sec;

  printf("\n");
  printf("  The program colors is %s\n",
         (ENABLE_COLORS) ? "\x1b[1;34mENABLED\x1b[0m" : "DISABLED");
  printf("\n");

  return 0;
}
