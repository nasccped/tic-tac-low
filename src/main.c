#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/const_vars.h"
#include "../include/game/rooms.h"
#include "../include/tests.h"
#include "../include/utils.h"
#include "../include/visuals.h"

// catching enable colors from <const_vars> header
unsigned ENABLE_COLORS;

// main function
int main(int argc, char *argv[]) {

  // initiate the random trigger
  srand(time(NULL));

  // max args that can be received: 1
  if ((argc - 1) > 1) {

    // printing unexpected arg count
    printf("\n");
    printf("  Unexpected args being received (count: %d)\n",
           argc - 1);

    // printing each arg
    for (int i = 1; i < argc; i++) {
      printf("  . %s\n", argv[i]);
    }

    // max argc count hint
    printf("\n");
    printf("  Maximum expected: 1\n");
    printf("\n");

    return 1;
  }

  // if arg count is exatcly 1 (expected)
  if ((argc - 1) == 1) {

    // call test function, then return
    main_test(argv[1]);
    return 0;
  }

  // storing yes/no user responsa as int
  int color_trigger;

  clear_terminal();

  // asking for colors
  printf("\n");
  printf("  Did you want to enable colors in the program? "
         "(yes / no | anything to quit)\n");

  printf("  > ");

  // if quit was called
  if ((color_trigger = yes_or_no_input()) == -1) {

    clear_terminal();

    // quit print
    printf("\n");
    printf("  Quitting...\n");
    printf("\n");

    // terminate
    return 0;
  }

  // update var (only > -1 values)
  ENABLE_COLORS = color_trigger;

  // loop variable default values
  int game_running = 1;
      MAIN_GAME_ROOM = MAIN_MENU;

  // program main loop
  while (game_running) {

    // clear terminal
    clear_terminal();

    // especific room run
    switch (MAIN_GAME_ROOM) {

      // if in menu
      case MAIN_MENU:
        menu_call(&MAIN_GAME_ROOM, ENABLE_COLORS);
        break;

      // if playing the game
      case PLAYING:
        game_call(&MAIN_GAME_ROOM, ENABLE_COLORS);
        break;

      // if in about page
      case ABOUT:
        about_call(&MAIN_GAME_ROOM, ENABLE_COLORS);
        break;

      // if quit
      case QUIT:

        // update loop trigger
        game_running = 0;
        break;
    } 
  }

  // printing bye text
  printf("\n");
  printf(" Quitting...\n");
  printf("\n");

  return 0;
}
