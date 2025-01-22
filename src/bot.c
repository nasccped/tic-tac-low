#include "../include/game/bot.h"


int get_move_pos(Bot *self, Table *tb) {

  // NOTE: priority:
  //    1 - win
  //    2 - don't lose
  //    3 - play on the most random way (human as hell)

  int holder;

  unsigned row[3],
           col[3];

  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 3; j++)
      row[j] = tb -> table_literal[i][j];

    for (int j = 0; j < 3; j++)
      col[j] = tb -> table_literal[j][i];

    if ((holder = self -> array_checker(self, row, 3, VICTORY)) != 0) {
      return (3 * (2 - i)) + 1 + holder;
    }

    if ((holder = self -> array_checker(self, col, 3, VICTORY)) != 0) {
      return (9 - (i * 3)) - (2 - holder);
    }
  }
  
  return 0;
}

int array_checker(Bot          *self ,
                  unsigned     *array,
                  unsigned      len  ,
                  BotLookingFor looking_for) {

  unsigned bot_val = self -> bot_val,
           count_bot_val            ,
           count_enemy_val          ,
           last_available           ;

  for (int i = 0; i < len; i++) {
    
    if (array[i] == bot_val)
      count_bot_val++;
    else if (array[i] != 0)
      count_enemy_val++;
    else
      last_available = i;
  }

  if (count_bot_val == 2 && looking_for == VICTORY)
    return last_available;

  if (count_enemy_val == 2 && looking_for == DEFENSE)
    return last_available;

  return 0;
}
