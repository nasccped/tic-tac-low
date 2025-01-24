#include <stdlib.h>
#include "../include/game/bot.h"
#include "../include/utils.h"

int get_move_pos(Bot *self, Table *tb) {

  // TODO: what I exactly need to do?
  // 1. Check for victory
  // 2. Avoid lose
  // 3. Play smart
  // 4. Play randomly
  //
  // NOTE: to check for victory, I need to
  // - check horizontaly
  // - check verticaly
  // - check diagonaly
  //
  // NOTE: to avoid lose, I need to
  // - check horizontaly
  // - check verticaly
  // - check diagonaly

  unsigned holder;

  BotAvailableCells *mbac = &MAIN_BAC;
  mbac -> cells = NULL;
  mbac -> len   = 0   ;

  if ((holder = self -> bot_check_vic(self, tb)) > 0)
    return holder;

  if ((holder = self -> bot_avoid_lose(self, tb)) > 0)
    return holder;

  self -> bot_smart_play(self, mbac, tb);

    holder = chose_random_uns(mbac -> cells, mbac -> len);

  free(mbac -> cells);
  mbac -> len = 0;

  return holder;
}

int bot_check_vic(Bot *self, Table *tb) {

  unsigned a, b, c;

  unsigned *collec[3] = {
    &a, &b, &c
  };

  unsigned b_val = self -> bot_val               ,
           enemy = (self -> bot_val == 2) ? 1 : 2;

  int one_cell_available;

  for (int i = 0; i < 3; i++) {

    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    one_cell_available = (
      !find_on_arr(*collec, enemy, 3)
      && (a + b + c) == (b_val * 2)
    );

    if (one_cell_available) {
      if (a == 0)
        return convert_row_col_intouns(i, 0);

      if (b == 0)
        return convert_row_col_intouns(i, 1);

      if (c == 0)
        return convert_row_col_intouns(i, 2);
    }

    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    one_cell_available = (
      !find_on_arr(*collec, enemy, 3)
      && (a + b + c) == (b_val * 2)
    );

    if (one_cell_available) {
      if (a == 0) 
        return convert_row_col_intouns(0, i);

      if (b == 0)
        return convert_row_col_intouns(1, i);

      if (c == 0)
        return convert_row_col_intouns(2, i);
    } 
  }
  
  for (int i = 0; i < 3; i += 2) {

    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    one_cell_available = (
      !find_on_arr(*collec, enemy, 3)
      && (a + b + c) == (b_val * 2)
    );

    if (one_cell_available) {
      if (a == 0)
        return convert_row_col_intouns(0, i);

      if (b == 0)
        return convert_row_col_intouns(1, 1);

      if (c == 0)
        return convert_row_col_intouns(2, 2 - i);
    }
  }

  return 0;
}

int bot_avoid_lose(Bot *self, Table *tb) {

  unsigned a, b, c;

  unsigned *collec[3] = {
    &a, &b, &c
  };

  unsigned b_val = self -> bot_val               ,
           enemy = (self -> bot_val == 2) ? 1 : 2;

  int one_cell_available;

  for (int i = 0; i < 3; i++) {

    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    if (one_cell_available) {
      if (a == 0)
        return convert_row_col_intouns(i, 0);

      if (b == 0)
        return convert_row_col_intouns(i, 1);

      if (c == 0)
        return convert_row_col_intouns(i, 2);
    }

    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    if (one_cell_available) {
      if (a == 0) 
        return convert_row_col_intouns(0, i);

      if (b == 0)
        return convert_row_col_intouns(1, i);

      if (c == 0)
        return convert_row_col_intouns(2, i);
    } 
  }
  
  for (int i = 0; i < 3; i += 2) {

    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    one_cell_available = (
      !find_on_arr(*collec, b_val, 3)
      && (a + b + c) == (enemy * 2)
    );

    if (one_cell_available) {
      if (a == 0)
        return convert_row_col_intouns(0, i);

      if (b == 0)
        return convert_row_col_intouns(1, 1);

      if (c == 0)
        return convert_row_col_intouns(0, 2 - i);
    }
  }

  return 0;
}

void bot_smart_play(Bot *self, BotAvailableCells *bac, Table *tb) {

  if (bac -> cells != NULL)
    free(bac -> cells);

  bac -> len = 0;

  unsigned enemy = self -> bot_val == 2 ? 1 : 2;

  unsigned *available_cells = (unsigned *)malloc(sizeof(unsigned) * 9);

  if (tb -> table_literal[1][1] == 0) {
    available_cells[0] = convert_row_col_intouns(1, 1);
    bac -> cells = available_cells;
    bac -> len = 1;
    return;
  }

  unsigned tl = tb -> table_literal[0][0],
           dr = tb -> table_literal[2][2],
           dl = tb -> table_literal[2][0],
           tr = tb -> table_literal[0][2];

  unsigned cur_cell;

  int tl_dr_play = (tl == enemy && dr == enemy),
      dl_tr_play = (dl == enemy && tr == enemy),
      mid_hon_ver                              ;

  if (tl_dr_play || dl_tr_play) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cur_cell = tb -> table_literal[i][j];
        mid_hon_ver = (i == 1 || j == 1);
        if (cur_cell == 0 && mid_hon_ver) {
          available_cells[bac -> len] = convert_row_col_intouns(i, j);
          bac -> len++;
        }
      }
    }
  } else {
    for (int i = 0; i < 3; i += 2) {
      for (int j = 0; j < 3; j += 2) {
        cur_cell = tb -> table_literal[i][j];
        if (cur_cell == 0) {
          available_cells[bac -> len] = convert_row_col_intouns(i, j);
          bac -> len++;
        }
      }
    }
  }

  if (tb -> table_literal[1][1] == 0) {
    available_cells[bac -> len] = convert_row_col_intouns(1, 1);
    bac -> len++;
  }

  bac -> cells = available_cells;
}
