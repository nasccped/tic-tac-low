#include <stdio.h>
#include "../include/visuals.h"
#include "../include/const_vars.h"

// Self explanatory
void clear_terminal() {
  printf("\x1b[2J\x1b[H");
}

/*
 * Self explanatory too
 *
 * Input:
 *    - unsigned val (enable_colors) for color escape triggers
 * */
void print_banner(unsigned enable_colors) {

  unsigned row_len = (
    sizeof(BANNER_ART[0]) / sizeof(BANNER_ART[0][0])
  );

  // printing banner top border
  printf("\n");
  printf("  %s", enable_colors ? BOLD_WHITE_NONE : "");

  for (int i = 0; i < row_len - 10; i++)
    printf("-");

  printf("%s\n", enable_colors ? RESET_ESCAPE : "");

  char cur;

  for (int i = 0; i < BANNER_ROW_COUNT; i++) {

    // left padding
    printf("  ");

    // iterate through each banner array element
    for (int j = 0; j < row_len; j++) {

      // update the holder
      cur = BANNER_ART[i][j];

      // print color escape based on cur value (or, print the self
      // char)
      switch (cur) {

        case '1':
          printf("%s", enable_colors ? BOLD_RED_NONE : "");
          break;

        case '2':
          printf("%s", enable_colors ? BOLD_GREEN_NONE : "");
          break;

        case '3':
          printf("%s", enable_colors ? BOLD_YELLOW_NONE : "");
          break;

        default:
          printf("%c", cur);
      }
    }
    printf("\n");
  }

  printf("%s", enable_colors ? RESET_ESCAPE : "");

  // printing banner bottom border
  printf("\n");
  printf("  %s", enable_colors ? BOLD_WHITE_NONE : "");

  for (int i = 0; i < row_len - 10; i++)
    printf("-");

  printf("%s\n", enable_colors ? RESET_ESCAPE : "");
}
