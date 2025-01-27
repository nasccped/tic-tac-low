#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/const_vars.h"
#include "../include/game/bot.h"
#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/utils.h"
#include "../include/visuals.h"

/*
 * A function to take a GameMessage struct and print its contents
 * based on their status + literal message
 *
 * Input:
 *    - GameMessage structpointer (self)
 *    - int value (enable_colors) for color trigger
 *
 * Output:
 *    None. Just prints
 * */
void print_message(GameMessage *self, int enable_colors) {

  // holding the type / message
  MessageType *type = &(self -> type);
  char *message = self -> message;

  // printing top border + its escapes
  printf("  %s------------------------------------------------------"
         "---------------%s\n",

         enable_colors ? BOLD_WHITE_NONE : "",
         enable_colors ? RESET_ESCAPE    : "");

  // specific text + escapes printing for each type scenario
  switch (self -> type) {

    case OK_AWAITING:
      printf("   %s AWAITING: %s "                 ,
             enable_colors ? BOLD_WHITE_YELLOW : "",
             enable_colors ? RESET_ESCAPE      : "");
      break;

    case OK_WINS:
      printf("   %s WIN: %s "                     ,
             enable_colors ? BOLD_WHITE_GREEN : "",
             enable_colors ? RESET_ESCAPE     : "");
      break;

    case OK_BREAK_EVEN:
      printf("   %s BREAK EVEN: %s "              ,
             enable_colors ? BOLD_WHITE_GREEN : "",
             enable_colors ? RESET_ESCAPE     : "");
      break;

    case ERR_NON_NUMERIC:
      printf("   %s ERROR-NUMERIC: %s "         ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : "");
      break;

    case ERR_OUT_OF_RANGE:
      printf("   %s ERROR-RANGE: %s "           ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : "");
      break;

    case ERR_CELL_ALREADY_TAKEN:
      printf("   %s ERROR-CELL: %s "            ,
             enable_colors ? BOLD_WHITE_RED : "",
             enable_colors ? RESET_ESCAPE   : "");
      break;
  }

  // print the message
  printf("%s\n", message);

  // printing the bottom border
  printf("  %s------------------------------------------------------"
         "----------------%s\n",

         enable_colors ? BOLD_WHITE_NONE : "",
         enable_colors ? RESET_ESCAPE    : "");
}

/*
 * A function to update the GameMessage's type and message
 *
 * Input:
 *    - GameMessage struct pointer (self)
 *    - MessageType enum (type)
 *    - string <char pointer> (messsage)
 *
 * Output:
 *    Nothing. Just updates the GameMessage struct values
 * */
void update_game_message(GameMessage *self, MessageType type, char *message) {

  self -> type = type;

  if (strlen(message) >= MESSAGE_MAX_LEN)
    strcpy(self -> message, "[UNABLE TO COPY+PASTE MESSAGE]");
  else
    strcpy(self -> message, message);
}

/*
 * The Lego Megazord game logic, which all struct types are docked
 * to make this bad idea works like (hell yeah, it's working), but
 * can unexpectedly thrown an error
 *
 * Input:
 *    - int value (enable_colors) for color escape trigger
 *    - int value (against_bot) to set game mod (player vs player or
 *      player vs bot)
 *
 * Output:
 *    Nothing. Just run the game
 * */
void gameplay_function(int enable_colors, int against_bot) {

  // holding many static values with alias
  Table *tb = &MAIN_TABLE;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;
  GameMessage *gm_msg = &MAIN_GAME_MESSAGE;
  Bot *bot = &MAIN_BOT;

  // reseting the table
  tb -> reset_table(tb);

  // store user's input + the same input as unsigned
  char store_input[INPUT_MAX_LEN];
  unsigned input_as_uns;

  // holdign some values, like
  int playing = 1,                   // if game is running
      player_turn = 1,               // player tunr
      bot_turn = 0,                  // if is bot turn
      table_status =
        tb -> check_for_victory(tb); // table status (win, even, running)

  // holding sleep times:
  unsigned sleeps[] = {1, 2, 3, 4}, // options
           slp_len = 4;             // options length

  // initially updates the Game Massege to a default value
  gm_msg -> update(gm_msg, OK_AWAITING, "Waiting for player 1 move");

  // infinite loop (breakable) for game run
  while (1) {

    // if is not playing, terminate the game
    if (!playing)
      break;

    // test table status
    switch (table_status) {
      // if break even
      case 0:
        gm_msg -> update(gm_msg, OK_BREAK_EVEN, "Break even");
        break;

      // if player 1 wins
      case 1:
        gm_msg -> update(gm_msg, OK_WINS, "Player 1 wins");
        break;

      // if player 2 wins
      case 2:
        gm_msg -> update(gm_msg, OK_WINS, "Player 2 wins");
        break;

      // table status can be also -1, but it doesn't need gm msg's
      // update 'cause it means that the game is still running
    }

    // clear terminal + print visuals:
    clear_terminal();
    printf("\n");                                   // line break
    gm_msg -> print_message(gm_msg, enable_colors); // Game message
    tb -> draw_table(tb, enable_colors);            // table itself

    // if no remaining cells at the table
    if (table_status != -1) {

      // ask for play again
      printf("\n  Did you want to play again? (yes/no)\n");
      printf("  > ");

      // if positive response
      if (yes_or_no_input() == 1) {

        // reset table
        tb -> reset_table(tb);

        // update message
        gm_msg -> update(gm_msg     ,
                         OK_AWAITING,
                         "Waiting for player 1 move");

        // reset values
        player_turn  =  1;
        table_status = -1;
        bot_turn     =  0;

      } else {

        // else, update loop breaker trigger
        playing = 0;
      }

      // go to the loop's head
      continue;
    }

    // if it's bot turn
    if (bot_turn) {

      // print waiting message
      printf("\n  ... \n");

      // get the bot move + sleep
      input_as_uns = bot -> get_move_pos(bot, tb);
      p_sleep(chose_random_uns(sleeps, slp_len));

    } else {

      // but, if not the bot's turn
      // ask for a position
      printf("\n  Choose a table cell based on numeric k.board "
             "(1..9)\n");

      // hold input on the 'store_position'
      p_input("  > ", store_input, INPUT_MAX_LEN);

      // if response isn't numeric
      if (!is_num(store_input, strlen(store_input))) {

        // update message
        gm_msg -> update(gm_msg         ,
                         ERR_NON_NUMERIC,
                         player_turn == 1
                         ? "Given input is invalid (Non numeric). "
                           "Player 1 turn"

                         : "Given input is invalid (Non numeric). "
                           "Player 2 turn");

        // goto loop's head
        continue;
      }

      // convert input string into numeric
      input_as_uns = atoi(store_input);

      // if invalid num
      if (input_as_uns > 9 || input_as_uns < 1) {

        // udpate message
        gm_msg -> update(gm_msg          ,
                         ERR_OUT_OF_RANGE,
                         player_turn == 1
                         ? "Given input is out of range (1..9). "
                           "Player 1 turn"

                         : "Given input is out of range (1..9). "
                           "Player 2 turn");

        // goto loop's head
        continue;
      }
    }

    // update CatchPlayerMove struct values
    p_move -> get_move(p_move, player_turn, input_as_uns);
    
    // if chosen cell isn't changeable
    if (!tb -> change_on_table(tb, p_move)) {

      // update message
      gm_msg -> update(gm_msg                ,
                       ERR_CELL_ALREADY_TAKEN,
                       player_turn == 1
                       ? "This cell has already been chosen. "
                         "Player 1 turn"

                       : "This cell has already been chosen. "
                         "Player 2 turn");

      // ...
      continue;
    }

    // alternate in player_turn value in [1, 2]
    player_turn = (player_turn % 2) + 1;

    // update table status
    table_status = tb -> check_for_victory(tb);

    // if isn't the bot turn (is player) and you against the bot
    if (!bot_turn && against_bot) {

      // set bot turn on
      bot_turn = 1;

      // update message
      gm_msg -> update(gm_msg     ,
                       OK_AWAITING,
                       "Waiting for Bot Play");

      // ...
      continue;
    }

    // else (is bot turn or your aren't against a bot)
    // set bot turn off
    bot_turn = 0;

    // update the message
    gm_msg -> update(gm_msg     ,
                     OK_AWAITING,
                     player_turn == 1
                     ? "Waiting for player 1 move"
                     : "Waiting for player 2 move");
  }

  // NOTE: I know, I know. 'But dude?! Why don't you use recursion
  // instead of a while loop? It's much simpler'.
  // I was thinking about it too, but it will take more mem in each
  // recursion turn (new variables, new pointer, ...)
  // Let's leave it this way :^D
}
