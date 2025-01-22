#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/const_vars.h"
#include "../include/visuals.h"
#include "../include/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_message(GameMessage *self, int enable_colors) {

  if (self == NULL)
    return;

  MessageType *type    = &(self -> type);
  char        *message = self -> message;

  printf("  %s----------------------------------------------------------------------%s\n",
         enable_colors ? BOLD_WHITE_NONE : "",
         enable_colors ? RESET_ESCAPE    : ""
  );

  switch (self -> type) {

    case OK_AWAITING:
      printf("   %s AWAITING: %s "                    ,
             enable_colors ? BOLD_WHITE_YELLOW : "",
             enable_colors ? RESET_ESCAPE      : ""
      );
      break;

    case OK_WINS:
      printf("   %s WIN: %s "                        ,
             enable_colors ? BOLD_WHITE_GREEN : "",
             enable_colors ? RESET_ESCAPE     : ""
      );
      break;

    case OK_BREAK_EVEN:
      printf("   %s BREAK EVEN: %s "                 ,
             enable_colors ? BOLD_WHITE_GREEN : "",
             enable_colors ? RESET_ESCAPE     : ""
      );
      break;

    case ERR_NON_NUMERIC:
      printf("   %s ERROR-NUMERIC: %s "            ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : ""
      );
      break;

    case ERR_OUT_OF_RANGE:
      printf("   %s ERROR-RANGE: %s "              ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : ""
      );
      break;

    case ERR_CELL_ALREADY_TAKEN:
      printf("   %s ERROR-CELL: %s "               ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : ""
      );
      break;
  }

  printf("%s\n", message);

  printf("  %s----------------------------------------------------------------------%s\n",
         enable_colors ? BOLD_WHITE_NONE : "",
         enable_colors ? RESET_ESCAPE    : ""
  );
}

void update_game_message(GameMessage *self, MessageType type, char *message) {

  if (self == NULL)
    return;

  self -> type = type;

  if (strlen(message) >= MESSAGE_MAX_LEN)
    strcpy(self -> message, "[UNABLE TO COPY+PASTE MESSAGE]");
  else
    strcpy(self -> message, message);
}

void player_vs_player_game(int enable_colors) {

  Table           *tb     = &MAIN_TABLE       ;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;
  GameMessage     *gm_msg = &MAIN_GAME_MESSAGE;

  char     store_input[INPUT_MAX_LEN];
  unsigned input_as_uns              ;

  int playing      = 1,
      player_turn  = 1,
      table_status = tb -> check_for_victory(tb);

  gm_msg -> update(gm_msg, OK_AWAITING, "Waiting for player 1 move");

  while (1) {

    if (!playing)
      break;

    switch (table_status) {
      case 0:
        gm_msg -> update(gm_msg, OK_BREAK_EVEN, "Break even");
        break;

      case 1:
        gm_msg -> update(gm_msg, OK_WINS, "Player 1 wins");
        break;

      case 2:
        gm_msg -> update(gm_msg, OK_WINS, "Player 2 wins");
        break;
    }

    clear_terminal();

    printf("\n");

    gm_msg -> print_message(gm_msg, 1);

    tb -> draw_table(tb, enable_colors);

    if (table_status != -1) {
      printf("\n  Did you want to play again? (yes/no)\n");
      printf("  > ");

      if (yes_or_no_input() == 1) {

        tb -> reset_table(tb);

        gm_msg -> update(gm_msg     ,
                         OK_AWAITING,
                         "Waiting for player 1 move"
        );

        player_turn  =  1;
        table_status = -1;

      } else {
        playing = 0;
      }
      continue;
    }

    printf("\n  Choose a table cell based on numeric k.board (1..9)\n");
    p_input("  > ", store_input, INPUT_MAX_LEN);

    if (!is_num(store_input, strlen(store_input))) {

      gm_msg -> update(gm_msg         ,
                       ERR_NON_NUMERIC,
                       player_turn == 1
                       ? "Given input is invalid (Non numeric). Player 1 turn"
                       : "Given input is invalid (Non numeric). Player 2 turn"
      );

      continue;
    }

    input_as_uns = atoi(store_input);

    if (input_as_uns > 9 || input_as_uns < 1) {

      gm_msg -> update(gm_msg          ,
                       ERR_OUT_OF_RANGE,
                       player_turn == 1
                       ? "Given input is out of range (1..9). Player 1 turn"
                       : "Given input is out of range (1..9). Player 2 turn"
      );

      continue;
    }

    p_move -> get_move(p_move, player_turn, input_as_uns);

    
    if (!tb -> change_on_table(tb, p_move)) {

      gm_msg -> update(gm_msg                ,
                       ERR_CELL_ALREADY_TAKEN,
                       player_turn == 1
                       ? "This cell has already been chosen. Player 1 turn"
                       : "This cell has already been chosen. Player 2 turn"
      );

      continue;
    }

    player_turn = (player_turn % 2) + 1;

    table_status = tb -> check_for_victory(tb);

    gm_msg -> update(gm_msg     ,
                     OK_AWAITING,
                     player_turn == 1
                     ? "Waiting for player 1 move"
                     : "Waiting for player 2 move"
    );

  }

  printf("\n  The loop has been break\n");

}

void player_vs_bot_game() {

  // TODO: implements the game here...
  printf("TODO!\n");
}
