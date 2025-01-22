#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/const_vars.h"
#include "../include/visuals.h"
#include "../include/utils.h"

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

  int playing = 1;

  while (1) {

    if (!playing)
      break;

    clear_terminal();
    printf("\n  Did you want to continue? (yes/no)\n");
    printf("  > ");

    playing = yes_or_no_input() > 0 ? 1 : 0;
  }

  printf("\n  The loop has been break\n");

}

void player_vs_bot_game() {

  // TODO: implements the game here...
  printf("TODO!\n");
}
