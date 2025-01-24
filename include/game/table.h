#ifndef _TABLE_H
#define _TABLE_H

#ifndef _PLAYER_H
#include "./player.h"
#endif

typedef struct Table {
  unsigned table_literal[3][3];

  int  (*check_for_victory)(struct Table *);
  void (*reset_table)(struct Table *);
  int  (*change_on_table)(struct Table *          ,
                          struct CatchPlayerMove *);
  void (*draw_table)(struct Table *, int);
} Table;

int  check_for_victory(struct Table *);
void reset_table(struct Table *);
int  change_on_table(struct Table *, struct CatchPlayerMove *);
void draw_table(struct Table *, int);

static Table MAIN_TABLE = {
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  &check_for_victory,
  &reset_table,
  &change_on_table,
  &draw_table
};

#endif
