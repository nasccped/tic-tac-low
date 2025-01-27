#include <stdio.h>
#include "../include/const_vars.h"
#include "../include/game/player.h"
#include "../include/game/table.h"
#include "../include/utils.h"

/*
 * A function to check and return the game table status, such as
 * victory, break even, ...
 *
 * Input:
 *    - Table struct (self) for self analysis
 *
 * Output:
 *    Integer value based on the table status. If it has a player
 *    victory, will return 1, if player 2, will return 2.
 *    But, if it breaks even, will return a 0, else (cells still
 *    available), -1
 * */
int check_for_victory(Table *self) {

  // checkign 3 values per iteration (a table is 3x3, it makes sense)
  unsigned a, b, c;

  // store the values pointer in an array
  unsigned *abc_collec[3] = {
    &a, &b, &c
  };

  // var to test if it has available cells
  int still_runing = 0;

  for (int i = 0; i < 3; i++) {

    // checking for horizontals
    a = self -> table_literal[i][0];
    b = self -> table_literal[i][1];
    c = self -> table_literal[i][2];

    // if 0 is on array (cells available)
    if (find_on_arr(*abc_collec, 0, 3))
      still_runing++; // increment

    // if all values are equals (but not 0)
    if (a == b && b == c && c != 0)
      return c; // return it

    // checking for verticals
    a = self -> table_literal[0][i];
    b = self -> table_literal[1][i];
    c = self -> table_literal[2][i];

    // same as above
    if (a == b && b == c && c != 0)
      return c;

    // if iter on mid pos, skip tests to next iter
    if (i == 1)
      continue;

    // checking for diagonals
    a = self -> table_literal[0][  i  ];
    b = self -> table_literal[1][  1  ];
    c = self -> table_literal[2][2 - i];

    // same as above
    if (a == b && b == c && c != 0)
      return c;
  }

  // if function still not returned
  // return -1 if cells available, else 0
  return (still_runing) ? -1 : 0;
}

/*
 * A function to reset the Table's struct values
 *
 * Input:
 *    - Table struct pointer (self)
 * */
void reset_table(Table *self) {

  // idiomatic way to do a 2D array loop
  int i = 0,
      j = 0;

  while (i < 3) {

    self -> table_literal[i][j] = 0;

    j++;

    if (j == 3) {
      i++;
      j = 0;
    }
  }
}

/*
 * A function to change the table values based on CatchPlayerMove
 * struct values
 *
 * Input:
 *    - Table struct pointer (self)
 *    - CatchPlayerMove struct pointer (catch_pmove)
 *
 * Output:
 *    It will return an integer (treated as bool).
 *      Everything was Ok   -> 1
 *      Something was Wrong -> 2
 * */
int change_on_table(Table *self, CatchPlayerMove *catch_pmove) {

  // cathing values from player move struct
  unsigned row = catch_pmove -> at_row    ,
           col = catch_pmove -> at_col    ,
           val = catch_pmove -> player_val;

  // if invalid values
  if (row > 2 || row < 0
     || col > 2 || col < 0
     || val < 1 || val > 2)
    return 0;

  // if table cell isn't available
  if (!(self -> cell_is_available(self, row, col)))
    return 0;

  // else
  // change on table + return OK
  self -> table_literal[row][col] = val;
  return 1;
}

/*
 * A function do display the table in a fancy way
 *
 * Input:
 *    - Table struct pointer (self)
 *    - integer value (enable_colors) for color trigger
 * */
void draw_table(Table *self, int enable_colors) {

  // store table symbols and the hieght length
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

  // var to hold table cells values
  unsigned a, b, c;

  for (int i = 0; i < 3; i++) {

    // update variable by row
    a = self -> table_literal[i][0];
    b = self -> table_literal[i][1];
    c = self -> table_literal[i][2];

    // visuals purely visuals
    printf("%s                        .-.                  .-.%s\n",
           enable_colors ? BOLD_WHITE_NONE : "",
           enable_colors ? RESET_ESCAPE    : "");

    // print each symbol row
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

/*
 * A function to test if a table's cell is available
 *
 * Input:
 *    - Table struct pointer (self)
 *    - integer value (row)
 *    - integer value (col)
 *
 * Output:
 *    Will return a integer value (treated as a bool). 1 if it's
 *    available, else 0
 * */
int cell_is_available(struct Table *self, int row, int col) {
  return self -> table_literal[row][col] == 0;
}
