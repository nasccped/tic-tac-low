#include <stdlib.h>
#include "../include/game/player.h"

/*
 * A function to get given values and update struct variables based
 * on these values.
 *
 * Input:
 *    - CatchPlayerMove struct pointer (dest) to insert values
 *    - unsigned value (player) to hold player symbol
 *    - unsigned value (pos) to hold the move position
 *
 * Output:
 *    Will return the dest pointer if it's success. Don't worry! The
 *    pointer won't be lost. The pointer return is used just to check
 *    success.
 * */
struct CatchPlayerMove *set_player_move(CatchPlayerMove *dest,
                                        unsigned player,
                                        unsigned pos) {

  // if invalid pos
  if (pos < 1 || pos > 9)
    return NULL;

  // if invalid player
  if (player < 1 || player > 2)
    return NULL;

  // default values
  unsigned row = 2,
           col = 0;

  // loop to catch 'row' and 'col' based on 'pos'
  for (int i = 0; i < (pos - 1); i++) {

    if (col == 2) {

      row--;
      col = 0;

      continue;
    }

    col++;
  }

  // update pointer values + return it
  dest -> at_col     = col   ;
  dest -> at_row     = row   ;
  dest -> player_val = player;

  return dest;
}
