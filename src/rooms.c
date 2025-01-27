#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/about.h"
#include "../include/const_vars.h"
#include "../include/game/game_literal.h"
#include "../include/game/rooms.h"
#include "../include/options.h"
#include "../include/utils.h"
#include "../include/visuals.h"

/*
 * A function to display / run the menu visuals and logics
 *
 * Input:
 *    - GameRoomEnum enum pointer (room) so it can be updated
 *    - int value (enable_colors) for escape trigger
 * */
void menu_call(enum GameRoomEnum *room, int enable_colors) {

  // variable to store the user's response
  char menu_resp[INPUT_MAX_LEN];

  // print visual
  print_banner(enable_colors);
  printf("\n");

  print_options(enable_colors, MENU_OPTIONS);
  printf("\n");

  // catch user's response
  p_input("  > ", menu_resp, INPUT_MAX_LEN);

  // if is valid (numeric)
  if (is_num(menu_resp, strlen(menu_resp))) {

    // change the game run based on its values
    switch (atoi(menu_resp)) {
      case 1:
        *room = PLAYING;
        break;

      case 2:
        *room = ABOUT;
        break;

      case 3:
        *room = QUIT;
        break;
    }
  };
}

/*
 * A function to display / run the gameplay function
 *
 * Input:
 *    - GameRoomEnum enum pointer (room) so it can be updated
 *    - int value (enable_colors) for escape trigger
 * */
void game_call(enum GameRoomEnum *room, int enable_colors) {

  // store user's response
  char menu_resp[INPUT_MAX_LEN];

  // print visuals
  print_banner(enable_colors);
  printf("\n");

  // ask for game mode (vs player / vs bot)
  printf("  Do you want to play against: "
         "(player / bot / anything to cancel)\n");

  p_input("  > ", menu_resp, INPUT_MAX_LEN);

  // call game function based on response (no call if invalid)
  if (strcmp(menu_resp, "player") == 0)
    gameplay_function(enable_colors, 0);
  else if (strcmp(menu_resp, "bot") == 0)
    gameplay_function(enable_colors, 1);

  // change room to default (menu)
  *room = MAIN_MENU;
}

/*
 * A function to display / run the gameplay function
 *
 * Input:
 *    - GameRoomEnum enum pointer (room) so it can be updated
 *    - int value (enable_colors) for escape trigger
 * */
void about_call(enum GameRoomEnum *room, int enable_colors) {
  // store user's response
  char menu_resp[INPUT_MAX_LEN];

  // print visuals
  print_banner(enable_colors);
  printf("\n");
  printing_about(enable_colors);

  // wait for response (value doesn't matter)
  p_input("  > Press Enter to continue ",
          menu_resp    ,
          INPUT_MAX_LEN);

  // change room to default (menu)
  *room = MAIN_MENU;
}
