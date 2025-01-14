#include <stdlib.h>
#include "../include/game/player.h"

struct CatchPlayerMove *set_player_move(struct CatchPlayerMove *dest, unsigned int player, unsigned pos) {

  if (pos < 1 || pos > 9)
    return NULL;

  if (player < 1 || player > 2)
    return NULL;

  if (dest == NULL)
    return NULL;

  unsigned row = 2,
           col = 0;

  for (int i = 0; i < (pos - 1); i++) {

    if (col == 2) {

      row--;
      col = 0;

      continue;
    }

    col++;
  }
  
  dest -> at_col     = col   ;
  dest -> at_row     = row   ;
  dest -> player_val = player;

  return dest;
}
