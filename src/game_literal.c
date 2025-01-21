#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/const_vars.h"
#include "../include/visuals.h"

#include <stdio.h>

void player_vs_player_game() {

  Table *tb = &MAIN_TABLE;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;

  int playing = 1,
      game_status = tb -> check_for_victory(tb);

  unsigned player_turn = 1,
           response_as_uns,
           cell           ;

  char alert[70] = "Player 1 turn. Awaiting response",
       response[INPUT_MAX_LEN];

  clear_terminal();

  printf("\n");
  printf("  --------------------------------------------------------------------\n");
  printf("  Alert: %s\n", alert);
  printf("  --------------------------------------------------------------------\n");
  printf("\n");

  tb -> draw_table(tb, 1);
}

void player_vs_bot_game() {

  // TODO: implements the game here...
  printf("TODO!\n");
}
