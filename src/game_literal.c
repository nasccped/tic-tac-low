#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/const_vars.h"
#include "../include/visuals.h"

#include <stdio.h>
#include <string.h>

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
         enable_colors ? BOLD_WHITE_NONE : ""
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

void player_vs_player_game() {

  Table           *tb     = &MAIN_TABLE       ;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;
  GameMessage     *gm_msg = &MAIN_GAME_MESSAGE;

  struct gm_msg_pair {
    MessageType type   ;
    char       *message;
  };

  struct gm_msg_pair pairs[] = {

    { OK_AWAITING     , "Hi there... I'm waiting for your move!" },
    { OK_WINS         , "Player 1 wins!"                         },
    { OK_BREAK_EVEN   , "You both break even"                    },
    { ERR_NON_NUMERIC , "Your input isn't a numeric value"       },
    { ERR_OUT_OF_RANGE, "Your input is out of range (1..9)"      },
  };

  int range = 5;

  clear_terminal();

  for (int i = 0;  i < range; i++) {

    gm_msg -> update(gm_msg, pairs[i].type, pairs[i].message);

    gm_msg -> print_message(gm_msg, 1);

    printf("\n");
  }
}

void player_vs_bot_game() {

  // TODO: implements the game here...
  printf("TODO!\n");
}
