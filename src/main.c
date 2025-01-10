#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _VISUALS_H
#include "./headers/visuals.h"
#endif

#ifndef _UTILS_H
#include "./headers/utils.h"
#endif

#ifndef _GAME_OPTIONS_H
#include "./headers/game_options.h"
#endif

#ifndef _TESTS_H
#include "./headers/tests.h"
#endif

unsigned ENABLE_COLORS;

void test();

// main function
int main(int argc, char *argv[]) {

  // max args that can be received: 1
  if ((argc - 1) > 1) {

    printf("\n");
    printf("  Unexpected args being received (count: %d)\n", argc - 1);
    for (int i = 1; i < argc; i++) {
      printf("  . %s\n", argv[i]);
    }

    printf("\n");
    printf("  Maximum expected: 1\n");
    printf("\n");

    return 1;
  }

  if ((argc - 1) == 1) {

    main_test(argv[1]);
    return 0;
  }

  // storing yes/no user responsa as int
  int color_trigger;

  clear_terminal();

  // asking for colors
  printf("\n");
  printf("  Did you want to enable colors in the program? (yes / no | anything to quit)\n");
  printf("  > ");

  // if quit was called
  if ((color_trigger = yes_or_no_input()) == -1) {

    clear_terminal();

    // quit print
    printf("\n");
    printf("  Quitting...\n");

    // terminate
    return 0;
  }

  // update var (only > -1 values)
  ENABLE_COLORS = color_trigger;

  clear_terminal();
  print_banner(ENABLE_COLORS);
  print_options(ENABLE_COLORS, MENU_OPTIONS);

  return 0;
}

void test() {

  printf("\n");
  printf("  This is the current test function.   xD\n");
  printf("\n");
}
