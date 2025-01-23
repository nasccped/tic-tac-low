#include "../include/game/bot.h"
#include "../include/utils.h"


int get_move_pos(Bot *self, Table *tb) {

  // TODO: what I exactly need to do?
  // 1. Check for victory
  // 2. Avoid lose
  // 3. Play smart
  // 4. Play randomly
  //
  // NOTE: (1) to check for victory, I need to
  // - check horizontaly
  // - check verticaly
  // - check diagonaly
  //
  // NOTE: (2) to avoid lose, I need to
  // - check horizontaly
  // - check verticaly
  // - check diagonaly

  int holder;

  if ((holder = self -> bot_check_vic(self, tb)) > 0)
    return holder;

  if ((holder = self -> bot_avoid_lose(self, tb)) > 0)
    return holder;

  return 0;
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
