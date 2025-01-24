#include <stdio.h>
#include <string.h>
#include "../include/options.h"
#include "../include/visuals.h"
#include "../include/const_vars.h"

void clear_terminal() { printf("\x1b[2J\x1b[H"); }

void print_banner(unsigned enable_colors) {

  unsigned row_len = sizeof(BANNER_ART[0]) / sizeof(BANNER_ART[0][0]);
  char cur;

  printf("\n");
  printf("  %s", enable_colors ? BOLD_WHITE_NONE : "");
  for (int i = 0; i < row_len - 10; i++)
    printf("-");

  printf("%s\n", enable_colors ? RESET_ESCAPE : "");

  for (int i = 0; i < BANNER_ROW_COUNT; i++) {

    printf("  ");

    for (int j = 0; j < row_len; j++) {

      cur = BANNER_ART[i][j];

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

  printf("\n");
  printf("  %s", enable_colors ? BOLD_WHITE_NONE : "");
  for (int i = 0; i < row_len - 10; i++)
    printf("-");
  printf("%s\n", enable_colors ? RESET_ESCAPE : "");
}

void print_options(unsigned enable_colors, const char *options[]) {

  // printing each option (last option as NULL is required!)
  for (int i = 0; strcmp(options[i], OPTION_END) != 0; i++) {
    printf("  %s%d%s. %s\n", enable_colors ? BOLD_YELLOW_NONE : "",
                             i + 1                                ,
                             enable_colors ? RESET_ESCAPE : ""    ,
                             options[i]
    );
  }
}
