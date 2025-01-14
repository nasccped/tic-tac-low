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

static struct Table tab_test1 = {
  {
    {1, 1, 1},
    {0, 0, 0},
    {0, 0, 0}
  },
  &check_for_victory,
  &reset_table,
};

static struct Table tab_test2 = {
  {
    {2, 0, 1},
    {2, 2, 2},
    {2, 2, 2}
  },
  &check_for_victory,
  &reset_table,
};

static struct Table tab_test3 = {
  {
    {2, 1, 1},
    {1, 2, 2},
    {1, 2, 1}
  },
  &check_for_victory,
  &reset_table,
};

static struct Table tab_test4 = {
  {
    {2, 1, 1},
    {1, 0, 2},
    {1, 2, 1}
  },
  &check_for_victory,
  &reset_table,
};

#endif
