#include "../include/game/bot.h"
#include "../include/utils.h"
#include <stdlib.h>


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

  unsigned holder            ,
           available_cells[9],
           aci = 0           ;

  MAIN_BAC.cells = NULL;
  MAIN_BAC.len   = 0   ;

  if ((holder = self -> bot_check_vic(self, tb)) > 0)
    return holder;

  if ((holder = self -> bot_avoid_lose(self, tb)) > 0)
    return holder;

  self -> bot_smart_play(self, &MAIN_BAC, tb);

  if (MAIN_BAC.len) {

    holder = chose_random_uns(MAIN_BAC.cells, MAIN_BAC.len);

    free(MAIN_BAC.cells);
    MAIN_BAC.len = 0;

  } else {

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        available_cells[aci] = convert_row_col_intouns(i, j);
        aci++;
      }
    }

    holder = chose_random_uns(available_cells, aci);
  }
  
  return holder;
}

int bot_check_vic(Bot *self, Table *tb) {

  unsigned a, b, c;

  unsigned *collec[3] = {
    &a, &b, &c
  };

  unsigned enemy = (self -> bot_val == 2) ? 1 : 2;

  int one_cell_available;

  for (int i = 0; i < 3; i++) {

    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    one_cell_available = !find_on_arr(*collec, enemy, 3)
                         && (a + b + c) == ((self -> bot_val) * 2);

    if (one_cell_available) {
      if (a == 0)
        return (3 * (2 - i)) + 1;

      if (b == 0)
        return (3 * (2 - i)) + 2;

      if (c == 0)
        return (3 * (2 - i)) + 3;
    }

    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    one_cell_available = !find_on_arr(*collec, enemy, 3)
                         && (a + b + c) == ((self -> bot_val) * 2);

    if (one_cell_available) {
      if (a == 0) 
        return i + 1 + 6;

      if (b == 0)
        return i + 1 + 3;

      if (c == 0)
        return i + 1;
    } 
  }

  
  for (int i = 0; i < 3; i += 2) {

    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    one_cell_available = !find_on_arr(*collec, enemy, 3)
                         && (a + b + c) == ((self -> bot_val) * 2);

    if (one_cell_available) {
      if (a == 0)
        return 6 + 1 + i;

      if (b == 0)
        return 5;

      if (c == 0)
        return 3 - i;
    }
  }

  return 0;
}

int bot_avoid_lose(Bot *self, Table *tb) {

  unsigned a, b, c;

  unsigned *collec[3] = {
    &a, &b, &c
  };

  unsigned enemy = (self -> bot_val == 2) ? 1 : 2;

  int one_cell_available;

  for (int i = 0; i < 3; i++) {

    a = tb -> table_literal[i][0];
    b = tb -> table_literal[i][1];
    c = tb -> table_literal[i][2];

    one_cell_available = !find_on_arr(*collec, self -> bot_val, 3)
                         && (a + b + c) == ((enemy) * 2);

    if (one_cell_available) {
      if (a == 0)
        return (3 * (2 - i)) + 1;

      if (b == 0)
        return (3 * (2 - i)) + 2;

      if (c == 0)
        return (3 * (2 - i)) + 3;
    }

    a = tb -> table_literal[0][i];
    b = tb -> table_literal[1][i];
    c = tb -> table_literal[2][i];

    one_cell_available = !find_on_arr(*collec, self -> bot_val, 3)
                         && (a + b + c) == ((enemy) * 2);

    if (one_cell_available) {
      if (a == 0) 
        return i + 1 + 6;

      if (b == 0)
        return i + 1 + 3;

      if (c == 0)
        return i + 1;
    } 
  }

  
  for (int i = 0; i < 3; i += 2) {

    a = tb -> table_literal[0][  i  ];
    b = tb -> table_literal[1][  1  ];
    c = tb -> table_literal[2][2 - i];

    one_cell_available = !find_on_arr(*collec, self -> bot_val, 3)
                         && (a + b + c) == ((enemy) * 2);

    if (one_cell_available) {
      if (a == 0)
        return 6 + 1 + i;

      if (b == 0)
        return 5;

      if (c == 0)
        return 3 - i;
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

  unsigned tl = tb -> table_literal[0][0],
           dr = tb -> table_literal[2][2],
           dl = tb -> table_literal[2][0],
           tr = tb -> table_literal[0][2];

  unsigned cur_cell;

  if ((tl == enemy && dr == enemy) || (dl == enemy && tr == enemy)) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cur_cell = tb -> table_literal[i][j];
        if (cur_cell == 0 && (i == 1 || j == 1)) {
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
