#include "../include/game/table.h"

int check_for_victory(struct Table *self) {

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

    if (a == b && b == c && c != 0)
      return c;

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }


    // checking for verticals
    a = self -> table_literal[0][i];
    b = self -> table_literal[1][i];
    c = self -> table_literal[2][i];

    if (a == b && b == c && c != 0)
      return c;

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }


    // checking for diagonals
    a = self -> table_literal[0][  i  ];
    b = self -> table_literal[1][  1  ];
    c = self -> table_literal[2][2 - i];

    if (a == b && b == c && c != 0)
      return c;

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }
  }

  return (still_runing) ? -1 : 0;
}

void reset_table(struct Table *self) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      self -> table_literal[i][j] = 0;
  }
}
