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

  unsigned bot_val;

  int (*get_move_pos)(struct Bot   *,
                      struct Table *);

} Bot;

int get_move_pos(struct Bot   *,
                 struct Table *);

static struct Bot MAIN_BOT = {
  2, &get_move_pos
};

#endif
