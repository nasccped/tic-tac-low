#include <stdio.h>
#include <time.h>
#include "../include/visuals.h"
#include "../include/utils.h"
#include "../include/options.h"
#include "../include/tests.h"

unsigned ENABLE_COLORS;

// main function
int main(int argc, char *argv[]) {

  srand(time(NULL));

  // max args that can be received: 1
  if ((argc - 1) > 1) {

    // printting unexpected arg count
    printf("\n");
    printf("  Unexpected args being received (count: %d)\n", argc - 1);

    // printting each arg
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
