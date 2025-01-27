#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/about.h"
#include "../include/const_vars.h"
#include "../include/game/game_literal.h"
#include "../include/game/rooms.h"
#include "../include/options.h"
#include "../include/tests.h"
#include "../include/utils.h"
#include "../include/visuals.h"

unsigned ENABLE_COLORS;

// main function
int main(int argc, char *argv[]) {

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
  ENABLE_COLORS  = color_trigger;

  int game_running = 1;
  MAIN_GAME_ROOM = MAIN_MENU;

  char menu_resp[INPUT_MAX_LEN];

  while (game_running) {

    clear_terminal();

    switch (MAIN_GAME_ROOM) {

      case MAIN_MENU:
        print_banner(ENABLE_COLORS);
        printf("\n");

        print_options(ENABLE_COLORS, MENU_OPTIONS);
        printf("\n");

        p_input("  > ", menu_resp, INPUT_MAX_LEN);

        if (is_num(menu_resp, strlen(menu_resp))) {

          switch (atoi(menu_resp)) {
            case 1:
              MAIN_GAME_ROOM = PLAYING;
              break;

            case 2:
              MAIN_GAME_ROOM = ABOUT;
              break;

            case 3:
              MAIN_GAME_ROOM = QUIT;
              break;
          }
        };

        break;

      case PLAYING:
        print_banner(ENABLE_COLORS);
        printf("\n");

        printf("  Do you want to play against: "
               "(player / bot / anything to cancel)\n");

        p_input("  > ", menu_resp, INPUT_MAX_LEN);

        if (strcmp(menu_resp, "player") == 0)
          gameplay_function(ENABLE_COLORS, 0);
        else if (strcmp(menu_resp, "bot") == 0)
          gameplay_function(ENABLE_COLORS, 1);

        MAIN_GAME_ROOM = MAIN_MENU;
        break;

      case ABOUT:
        print_banner(ENABLE_COLORS);
        printf("\n");
        printing_about(ENABLE_COLORS);
        p_input("  > Press Enter to continue",
                menu_resp    ,
                INPUT_MAX_LEN);

        MAIN_GAME_ROOM = MAIN_MENU;
        break;

      case QUIT:
        game_running = 0;
        break;
    } 

  }

  printf("\n");
  printf(" Quitting...\n");
  printf("\n");

  return 0;
}
