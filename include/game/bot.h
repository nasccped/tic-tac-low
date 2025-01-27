#ifndef _BOT_H
#define _BOT_H

#ifndef _TABLE_H
#include "./table.h"
#endif

typedef enum BotLookingFor {
  VICTORY,
  DEFENSE,
  RANDOM ,
} BotLookingFor;

typedef struct _BAC {
  unsigned *cells,
            len;
} BotAvailableCells;

typedef struct Bot {
  unsigned bot_val;

  int (*get_move_pos)(struct Bot   *,
                      struct Table *);
  int (*bot_check_vic)(struct Bot   *,
                       struct Table *);
  int (*bot_avoid_lose)(struct Bot   *,
                        struct Table *);
  void (*bot_smart_play)(struct Bot   *,
                         struct _BAC  *,
                         struct Table *);
} Bot;

int get_move_pos(struct Bot   *,
                 struct Table *);
int bot_check_vic(struct Bot   *,
                  struct Table *);
int bot_avoid_lose(struct Bot   *,
                   struct Table *);
void bot_smart_play(struct Bot   *,
                     struct _BAC  *,
                     struct Table *);

void catch_axis_cells(Bot *self, BotAvailableCells *bac, Table *tb);
void catch_side_cells(Bot *self, BotAvailableCells *bac, Table *tb);
void catch_all_cells(Bot *self, BotAvailableCells *bac, Table *tb);

static struct Bot MAIN_BOT = {
  2              ,
  &get_move_pos  ,
  &bot_check_vic ,
  &bot_avoid_lose,
  &bot_smart_play
};

static struct _BAC MAIN_BAC;

#endif
