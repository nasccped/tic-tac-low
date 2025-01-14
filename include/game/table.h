#ifndef _TABLE_H
#define _TABLE_H

struct Table {
  unsigned table_literal[3][3]             ;
  int  (*check_for_victory)(struct Table *);
  void (*reset_table      )(struct Table *);
};

int  check_for_victory(struct Table *);
void reset_table      (struct Table *);

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
