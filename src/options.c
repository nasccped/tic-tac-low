#include <stdio.h>
#include <string.h>
#include "../include/const_vars.h"
#include "../include/options.h"

/*
 * Self explanatory.
 *
 * Input:
 *    - unsigned value (enable_colors) for escapes trigger
 *    - string array <char pointers array> (options)
 *
 * Output:
 *    Nothing. Just prints
 * */
void print_options(unsigned enable_colors, const char *options[]) {

  // print tip
  printf("  Chose by option number:\n");

  // printing each option
  for (int i = 0; strcmp(options[i], OPTION_END) != 0; i++) {

    printf("    %s%d.%s %s\n",
           enable_colors ? BOLD_YELLOW_NONE : "",
           i + 1                                ,
           enable_colors ? RESET_ESCAPE : ""    ,
           options[i]                           );
  }
}
