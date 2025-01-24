#include <stdio.h>
#include "../include/about.h"
#include "../include/const_vars.h"

void printting_about(unsigned colors) {

  printf("  Hi there. %sNasccped%s here!\n",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "");
  printf("\n");

  printf("  This is %sTic-Tac-Low%s(Tic Tac Toe inspired game built entirely in %sC lang%s)!\n",
         colors ? BOLD_BLUE_NONE : "",
         colors ? RESET_ESCAPE   : "",
         colors ? BOLD_BLUE_NONE : "",
         colors ? RESET_ESCAPE   : "");
  printf("\n");

  printf("  - You can play against some %sfriend%s or a %sbot%s too (may have %sbugs%s).\n",
         colors ? BOLD_MAGENTA_NONE : "",
         colors ? RESET_ESCAPE      : "",
         colors ? BOLD_MAGENTA_NONE : "",
         colors ? RESET_ESCAPE      : "",
         colors ? BOLD_RED_NONE     : "",
         colors ? RESET_ESCAPE      : "");

  printf("  - Easy navigation through %scli suggestions%s (yes / no / numbers).\n",
         colors ? BOLD_MAGENTA_NONE : "",
         colors ? RESET_ESCAPE      : "");

  printf("  - Easy gameplay through %scomputer numeric keyboard%s:\n",
         colors ? BOLD_MAGENTA_NONE : "",
         colors ? RESET_ESCAPE      : "");

  printf("\n");

  printf("    %s7%s | %s8%s | %s9%s \n",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "");
  printf("   ---+---+---\n");
  printf("    %s4%s | %s5%s | %s6%s \n",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "");
  printf("   ---+---+---\n");
  printf("    %s1%s | %s2%s | %s3%s \n",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "",
         colors ? BOLD_YELLOW_NONE : "",
         colors ? RESET_ESCAPE     : "");

  printf("\n");
  printf("  Did you find a %sbug%s? Do you know how to %sfix%s?\n",
         colors ? BOLD_RED_NONE   : "",
         colors ? RESET_ESCAPE    : "",
         colors ? BOLD_GREEN_NONE : "",
         colors ? RESET_ESCAPE    : ""
         );
  printf("  Consider opening a issue/pull request at:\n"
         "    - %s%s%s\n",
         colors ? BOLD_YELLOW_NONE : "",
         REPOSITORY_URL                ,
         colors ? RESET_ESCAPE : "");

  printf("\n");

  printf("  This project is under the %sMIT%s license\n",
         colors ? BOLD_GREEN_NONE : "",
         colors ? RESET_ESCAPE    : "");

  printf("\n");
}
