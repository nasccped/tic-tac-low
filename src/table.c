#include "./headers/game/table.h"


int check_for_victory(unsigned *tb[3][3]) {

  unsigned a, b, c;

  unsigned *abc_collec[3] = {
    &a, &b, &c
  };

  int still_runing = 0;

  for (int i = 0; i < 3; i++) {

    a = *tb[0][  i  ];
    b = *tb[1][  1  ];
    c = *tb[2][2 - i];

    if (a == b && b == c && c != 0)
      return c;

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }

    a = *tb[  i  ][0];
    b = *tb[  1  ][1];
    c = *tb[2 - 1][2];

    if (a == b && b == c && c != 0)
      return c;

    for (int j = 0; j < 3; j++) {
      if (*abc_collec[j] == 0)
        still_runing++;
    }

  }

  return (still_runing) ? -1 : 0;
}

void reset_table(unsigned *self_table[3][3]) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      self_table[i][j] = 0;
  }
}
