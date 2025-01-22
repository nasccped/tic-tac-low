#ifndef _BOT_H
#define _BOT_H

#ifndef _TABLE_H
#include "./table.h"
#endif

typedef enum BotLookingFor {
  VICTORY,
  DEFENSE,
  RANDOM,
} BotLookingFor;

typedef struct Bot {

  unsigned bot_val    ,
           play_at_row,
           play_at_col;

  int (*array_checker)(struct Bot *,
                       unsigned   *,
                       unsigned    ,
                       enum BotLookingFor);

  int (*get_move_pos)(struct Bot   *,
                      struct Table *);

} Bot;

int get_move_pos(struct Bot   *,
                 struct Table *);

int array_checker(struct Bot *,
                  unsigned   *,
                  unsigned    ,
                  enum BotLookingFor);

static struct Bot MAIN_BOT = {

  2, 0, 0,

  &array_checker,
  &get_move_pos
};

#endif
