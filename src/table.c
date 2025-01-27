#include <stdio.h>
#include "../include/const_vars.h"
#include "../include/game/player.h"
#include "../include/game/table.h"

int check_for_victory(Table *self) {

  unsigned a, b, c;

  unsigned *abc_collec[3] = {
    &a, &b, &c
  };

  int still_runing = 0;

  for (int i = 0; i < 3; i++) {

    // checking for horizontals
    a = self -> table_literal[i][0];
    b = self -> table_literal[i][1];
    c = self -> table_literal[i][2];

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }

    if (a == b && b == c && c != 0)
      return c;

    // checking for verticals
    a = self -> table_literal[0][i];
    b = self -> table_literal[1][i];
    c = self -> table_literal[2][i];

    if (a == b && b == c && c != 0)
      return c;

    // checking for diagonals
    a = self -> table_literal[0][  i  ];
    b = self -> table_literal[1][  1  ];
    c = self -> table_literal[2][2 - i];

    if (a == b && b == c && c != 0)
      return c;
  }

  return (still_runing) ? -1 : 0;
}

void reset_table(Table *self) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      self -> table_literal[i][j] = 0;
  }
}

int change_on_table(Table *self, CatchPlayerMove *catch_pmove) {

  unsigned row = catch_pmove -> at_row    ,
           col = catch_pmove -> at_col    ,
           val = catch_pmove -> player_val;

  if (row > 2 || row < 0)
    return 0;

  if (col > 2 || col < 0)
    return 0;

  if (val < 1 || val > 2)
    return 0;

  if (!(self -> cell_is_available(self, row, col)))
    return 0;

  self -> table_literal[row][col] = val;

  return 1;
}

void draw_table(Table *self, int enable_colors) {

  const unsigned symbol_y_len = 5;

  char *p1_symbol[] = {
    "  Y8b Y8P  ",
    "   Y8b Y   ",
    "    Y8b    ",
    "   e Y8b   ",
    "  d8b Y8b  ",
  },
    *p2_symbol[] = {
    "  e88#88e  ",
    " d88P '88b ",
    "C88B   888D",
    " Y88b d88P ",
    "  '88#88'  ",
  },
    *empty_symbol[] = {
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
  };

  unsigned a, b, c;

  for (int i = 0; i < 3; i++) {

    a = self -> table_literal[i][0];
    b = self -> table_literal[i][1];
    c = self -> table_literal[i][2];

    printf("%s                        .-.                  .-.%s\n",
           enable_colors ? BOLD_WHITE_NONE : "",
           enable_colors ? RESET_ESCAPE    : "");

    for (int j = 0; j < symbol_y_len; j++) {

      printf("          %s%s%s   | |   %s%s%s    | |   %s%s%s\n",

             enable_colors && a == 1 ?
               BOLD_BLUE_NONE : enable_colors && a == 2 ?
                 BOLD_MAGENTA_NONE : "",

             a == 0 ?
               empty_symbol[j] : a == 1 ?
                 p1_symbol[j] : p2_symbol[j],

             enable_colors ? BOLD_WHITE_NONE : "",


             enable_colors && b == 1 ?
               BOLD_BLUE_NONE : enable_colors && b == 2 ?
                 BOLD_MAGENTA_NONE : "",

             b == 0 ?
               empty_symbol[j] : b == 1 ?
                 p1_symbol[j] : p2_symbol[j],

             enable_colors ? BOLD_WHITE_NONE : "",


             enable_colors && c == 1 ?
               BOLD_BLUE_NONE : enable_colors && c == 2 ?
                 BOLD_MAGENTA_NONE : "",

             c == 0 ?
               empty_symbol[j] : c == 1 ?
                 p1_symbol[j] : p2_symbol[j],

             enable_colors ? RESET_ESCAPE : "");
    
    }

    printf("%s                        '-'                  '-'%s\n",
           enable_colors ? BOLD_WHITE_NONE : "",
           enable_colors ? RESET_ESCAPE    : "");
  }

}

int cell_is_available(struct Table *self, int row, int col) {
  return self -> table_literal[row][col] == 0;
}
