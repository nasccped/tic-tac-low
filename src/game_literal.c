#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/const_vars.h"
#include "../include/visuals.h"
#include "../include/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void player_vs_player_game() {

  // TODO: implements the game here...
  printf("  Let's play a 2P game!\n");
}

void player_vs_bot_game() {

  // TODO: implements the game here...
  printf("TODO!\n");
}

void pvp_todo() {

  Table *tb = &MAIN_TABLE;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;

  int playing = 1,
      game_status = tb -> check_for_victory(tb);

  unsigned player_turn = 1,
           response_as_uns,
           cell           ;

  char alert[70] = "Player 1 turn. Awaiting response",
       response[INPUT_MAX_LEN];

  while (playing) {

    clear_terminal();

    printf("\n");
    printf("  Alert: %s\n", alert);
    printf("\n");

    for (int i = 0; i < 3; i++) {
      printf("      ");
      for (int j = 0; j < 3; j++) {
        cell = tb->table_literal[i][j];
        printf("%c  ", cell == 1 ? 'X' : cell == 2 ? 'O' : '_');
      }
      printf("\n");
    }

    printf("\n");
    p_input("  Chose a numeric keyboard position: ", response, INPUT_MAX_LEN);

    if (!is_num(response, strlen(response))) {

      switch (player_turn) {

        case 1:
          strcpy(alert, "Invalid response (non-numeric). Player 1 Turn");
          break;

        case 2:
          strcpy(alert, "Invalid response (non-numeric). Player 2 Turn");
          break;
      }
      continue;
    }

    response_as_uns = atoi(response);

    if (p_move->get_move(p_move, player_turn, response_as_uns) == NULL) {

      switch (player_turn) {

        case 1:
          strcpy(alert, "Invalid response (out of range 1..9). Player 1 Turn");
          break;

        case 2:
          strcpy(alert, "Invalid response (out of range 1..9). Player 2 Turn");
          break;
      }
      continue;
    }

    if (!tb->change_on_table(tb, p_move)) {

      switch (player_turn) {

        case 1:
          strcpy(alert, "Invalid response (cell already taken). Player 1 Turn");
          break;

        case 2:
          strcpy(alert, "Invalid response (cell already taken). Player 2 Turn");
          break;
      }
      continue;
    }

    game_status = tb->check_for_victory(tb);

    switch (player_turn) {

      case 1:
        strcpy(alert, "Player 2 Turn. Awaiting response");
        player_turn++;
        break;

      case 2:
        strcpy(alert, "Player 1 Turn. Awaiting response");
        player_turn--;
        break;
    }

    switch (game_status) {

      case -1:
        break;

      case 0:
        clear_terminal();
        printf("\n");
        printf("  You two tied!\n\n");
        for (int i = 0; i < 3; i++) {
          printf("      ");
          for (int j = 0; j < 3; j++) {
            cell = tb->table_literal[i][j];
            printf("%c  ", cell == 1 ? 'X' : cell == 2 ? 'O' : '_');
          }
          printf("\n");
        }
        printf("\n");
        printf("  Do you want to play again? (yes/no)\n");
        printf("  > ");
        playing = yes_or_no_input() > 0 ? 1 : 0;
        tb -> reset_table(tb);
        player_turn = 1;
        strcpy(alert, "Player 1 turn. Awaiting response");
        break;

      case 1:
        clear_terminal();
        printf("\n");
        printf("  Player 1 wins!\n\n");
        for (int i = 0; i < 3; i++) {
          printf("      ");
          for (int j = 0; j < 3; j++) {
            cell = tb->table_literal[i][j];
            printf("%c  ", cell == 1 ? 'X' : cell == 2 ? 'O' : '_');
          }
          printf("\n");
        }
        printf("\n");
        printf("  Do you want to play again? (yes/no)\n");
        printf("  > ");
        playing = yes_or_no_input() > 0 ? 1 : 0;
        tb -> reset_table(tb);
        player_turn = 1;
        strcpy(alert, "Player 1 turn. Awaiting response");
        break;

      case 2:
        clear_terminal();
        printf("\n");
        printf("  Player 2 wins!\n\n");
        for (int i = 0; i < 3; i++) {
          printf("      ");
          for (int j = 0; j < 3; j++) {
            cell = tb->table_literal[i][j];
            printf("%c  ", cell == 1 ? 'X' : cell == 2 ? 'O' : '_');
          }
          printf("\n");
        }
        printf("\n");
        printf("  Do you want to play again? (yes/no)\n");
        printf("  > ");
        playing = yes_or_no_input() > 0 ? 1 : 0;
        tb -> reset_table(tb);
        player_turn = 1;
        strcpy(alert, "Player 1 turn. Awaiting response");
        break;
    }
  }
}
