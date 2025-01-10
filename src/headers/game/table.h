#ifndef _TABLE_H
#define _TABLE_H

struct Table {
  unsigned table_literal[3][3]               ;
  int  (*check_for_victory)(unsigned *[3][3]);
  void (*reset_table      )(unsigned *[3][3]);
};

int  check_for_victory(unsigned *[3][3]);
void reset_table      (unsigned *[3][3]);

static struct Table MAIN_TABLE = {
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  &check_for_victory,
  &reset_table,
};

#endif
