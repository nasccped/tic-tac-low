#include <stdlib.h>
#include "../include/game/bot.h"
#include "../include/utils.h"

/*
 * A function to simulate a pseudo-player move (Bot)
 * 
 * Input:
 *    - Bot struct pointer (self)
 *    - Table struct pointer (tb) for analysis
 *
 * Output:
 *    - A numeric keyboard position value (1..9)
 * */
int get_move_pos(Bot *self, Table *tb) {

  // Priorities roadmap:
  //  - Win
  //  - Don't lose
  //  - Play smart
  //  - Play randomly

  // holder var (it will hold the final return value)
  unsigned holder;

  // an available cells struct (helps in randomly choices)
  BotAvailableCells *mbac = &MAIN_BAC;

  mbac -> cells = NULL;
  mbac -> len = 0;
  mbac -> append = &append_on_BAC;

  // if victory scenario exists (not 0), return it's position
  if ((holder = self -> bot_check_vic(self, tb)) > 0)
    return holder;

  // if don't lose scenario exists (not 0), return it's position
  if ((holder = self -> bot_avoid_lose(self, tb)) > 0)
    return holder;

  // else, insert available smart cells (read 'bot_smart_play'
  // func) on available cells struct
  self -> bot_smart_play(self, mbac, tb);

  // choose one of them
  holder = chose_random_uns(mbac -> cells, mbac -> len);

  // free allocated mem
  free(mbac -> cells);

  // reset len
  mbac -> len = 0;

  // return the chosen value
  return holder;
}

/*
 * A function to detect if bot victory scenario exists
 *
 * Input:
 *    - Bot struct pointer (self)
 *    - Table struct pointer (tb) for analysis
 *
 * Output:
 *    - A numeric keyboard position value for its victory if exists,
 *      else 0
 * */
int bot_check_vic(Bot *self, Table *tb) {

  // let's compare three adjacent per turn
  unsigned a, b, c;

  // storing these values pointers in an array
  unsigned *collec[3] = {
    &a, &b, &c
  };

  // getting the bot and enemy value
  unsigned b_val = self -> bot_val,
           enemy = (self -> bot_val == 2) ?
                   1 : 2;

  // store if is there one cell available
  int one_cell_available;

  // iter 3 times
  for (int i = 0; i < 3; i++) {

    // testing for a, b, c in a row
    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    // one cell is true only if:
    one_cell_available = (
      !find_on_arr(*collec, enemy, 3) // row doesn't contains enemy
                                      // values
      &&                              // and (&&)
      (a + b + c) == (b_val * 2)      // sum(row cells) is equals two
    );                                // bot vals

    // if one cell is true:
    if (one_cell_available) {
      // case left is empty
      if (a == 0)
        return convert_row_col_intouns(i, 0);

      // case mid is empty
      if (b == 0)
        return convert_row_col_intouns(i, 1);

      // case right is empty
      if (c == 0)
        return convert_row_col_intouns(i, 2);
    }

    // if function still not return

    // testing for a, b, c in a column
    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    // already explained
    one_cell_available = (
      !find_on_arr(*collec, enemy, 3)
      && (a + b + c) == (b_val * 2)
    );

    // if one cell is true
    if (one_cell_available) {
      // case top empty
      if (a == 0) 
        return convert_row_col_intouns(0, i);

      // case mid empty
      if (b == 0)
        return convert_row_col_intouns(1, i);

      // case bottom empty
      if (c == 0)
        return convert_row_col_intouns(2, i);
    }

    // if still not returned
    // case index is 1 (at mid pos)
    if (i == 1)
      // skip tests
      continue;

    // testing for a, b, c diagonaly (axis)
    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    // already explained
    one_cell_available = (
      !find_on_arr(*collec, enemy, 3)
      && (a + b + c) == (b_val * 2)
    );

    // if one cell is true
    if (one_cell_available) {
      // case top axis empty
      if (a == 0)
        return convert_row_col_intouns(0, i);

      // case mid empty
      if (b == 0)
        return convert_row_col_intouns(1, 1);

      // case bottom axis empty
      if (c == 0)
        return convert_row_col_intouns(2, 2 - i);
    }
  }

  // if none of previous conditions is true,
  // return 0 (no victory scenario)
  return 0;
}

/*
 * A function to detect if bot lose scenario exists
 *
 * Input:
 *    - Bot struct pointer (self)
 *    - Table struct pointer (tb) for analysis
 *
 * Output:
 *    - A numeric keyboard positioon values for not lose if exists,
 *      else 0
 * */
int bot_avoid_lose(Bot *self, Table *tb) {

  // same as above function (comparing adjacents)
  unsigned a, b, c;

  // storign it's pointer
  unsigned *collec[3] = {
    &a, &b, &c
  };

  // storegin bot and enemy val
  unsigned b_val = self -> bot_val,
           enemy = (self -> bot_val == 2) ?
                   1 : 2;

  // if one cell is available
  int one_cell_available;

  for (int i = 0; i < 3; i++) {

    // testing for a, b, c in a row
    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    // already explained in function above
    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    // if one cell empty
    if (one_cell_available) {
      // case left empty
      if (a == 0)
        return convert_row_col_intouns(i, 0);

      // case mid empty
      if (b == 0)
        return convert_row_col_intouns(i, 1);

      // case right empty
      if (c == 0)
        return convert_row_col_intouns(i, 2);
    }

    // testing for a, b, c in a column
    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    // explained in function above
    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    // if one cell empty
    if (one_cell_available) {
      // case top empty
      if (a == 0) 
        return convert_row_col_intouns(0, i);

      // case mid empty
      if (b == 0)
        return convert_row_col_intouns(1, i);

      // case bottom empty
      if (c == 0)
        return convert_row_col_intouns(2, i);
    }

    // skip if iteration at mid
    if (i == 1)
      continue;

    // testing for a, b, c diagonaly (axis)
    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    // already explained (function above)
    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    // if one cell empty
    if (one_cell_available) {
      // case top axis empty
      if (a == 0)
        return convert_row_col_intouns(0, i);

      // case mid empty
      if (b == 0)
        return convert_row_col_intouns(1, 1);

      // case bottom axis empty
      if (c == 0)
        return convert_row_col_intouns(2, 2 - i);
    }
  }

  // else (no not lose scenario)
  return 0;
}

/*
 * A function to catch possible future plays, do an 'auto-defense'
 * play, or if no future risk, play randomly
 *
 * Input:
 *    - Bot struct pointer (self)
 *    - BotAvailableCells struct pointer (bac) to store available
 *      position
 *    - Table struct pointer (tb) for analysis
 *
 * Output:
 *    - Nothing. This function will only change *bac values, so,
 *      these values can be chosen by a bot random function
 * */
void bot_smart_play(Bot *self, BotAvailableCells *bac, Table *tb) {

  // cells at bac is a pointer array, if it isn't NULL, free
  // and point to NULL
  if (bac -> cells != NULL) {
    free(bac -> cells);
    bac -> cells = NULL;
  }

  // updated len to 0
  bac -> len = 0;

  // catche enemy value
  unsigned enemy = self -> bot_val == 2 ? 1 : 2;

  // create a malloc unsigned array to store available
  // position (max is 9)
  unsigned *available_cells = (
    (unsigned *)malloc(sizeof(unsigned) * 9)
  );

  bac -> cells = available_cells;

  // if center is empty
  if (tb -> table_literal[1][1] == 0) {
    // add it to array and then return it
    bac -> append(bac, convert_row_col_intouns(1, 1));
    return;
  }

  // catching the most anti-human play against bots (diagonals)
  unsigned tl = tb -> table_literal[0][0], // top-left   cell
           dr = tb -> table_literal[2][2], // down-right cell
           dl = tb -> table_literal[2][0], // down-left  cell
           tr = tb -> table_literal[0][2]; // top-right  cell

  // var to store the current cell
  unsigned cur_cell;

  // if enemy doing diagonal plays >:^(
  int diagonal_play = (tl == enemy && dr == enemy)     // tl to dr
                      || (dl == enemy && tr == enemy); // dl to tr

  // if diagonal play
  if (diagonal_play)
    catch_side_cells(self, bac, tb);

  if (bac -> len)
    return;

  // else no diagonal play
  catch_axis_cells(self, bac, tb);

  if (bac -> len)
    return;

  catch_all_cells(self, bac, tb);
}

void catch_axis_cells(Bot *self, BotAvailableCells *bac, Table *tb) {
  
  unsigned b_val = self -> bot_val,
           enemy = self -> bot_val == 1 ? 2 : 1,
           cur_cell;

  for (int i = 0; i < 3; i += 2) {
    for (int j = 0; j < 3; j += 2) {
      cur_cell = tb -> table_literal[i][j];
      if (cur_cell == 0) {
        bac -> append(bac, convert_row_col_intouns(i, j));
      }
    }
  }
}

void catch_side_cells(Bot *self, BotAvailableCells *bac, Table *tb) {

  unsigned b_val = self -> bot_val,
           enemy = self -> bot_val == 1 ? 2 : 1,
           cur_cell;

  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 3; j++) {

      if (j % 2 == i % 2)
        continue;

      cur_cell = tb -> table_literal[i][j];

      if (cur_cell == 0)
        bac -> append(bac, convert_row_col_intouns(i, j));

    }
  }
}

void catch_all_cells(Bot *self, BotAvailableCells *bac, Table *tb) {

  unsigned b_val = self -> bot_val,
           enemy = self -> bot_val == 1 ? 2 : 1,
           cur_cell;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cur_cell = tb -> table_literal[i][j];
      if (cur_cell == 0)
        bac -> append(bac, convert_row_col_intouns(i, j));
    }
  }
}

void append_on_BAC(BotAvailableCells *self, unsigned value) {

  self -> cells[self -> len] = value;
  self -> len++;
}
