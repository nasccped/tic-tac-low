#include <stdio.h>
#include <string.h>
#include "../include/options.h"
#include "../include/const_vars.h"

void print_options(unsigned enable_colors, const char *options[]) {

  printf("  Chose by option number:\n");

  // printing each option (last option as NULL is required!)
  for (int i = 0; strcmp(options[i], OPTION_END) != 0; i++) {
    printf("    %s%d.%s %s\n", enable_colors ? BOLD_YELLOW_NONE : "",
                               i + 1                                ,
                               enable_colors ? RESET_ESCAPE : ""    ,
                               options[i]                           );
  }
}
