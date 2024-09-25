/* ------------------------------------------------------------------
 *
 * main.c
 *
 *     file responsible for store the main task and / or the
 *     combination of all tasks
 * ----------------------------------------------------------------*/
#include <stdio.h>

int main(int argc, char *argv[]) {

  const char *YELLOW_ESCAPE   = "\033[1;43m";
  const char *RESET_ESCAPE = "\033[0m"   ;

  printf("\t%s Hell %s Weirdo\n",
         YELLOW_ESCAPE          ,
         RESET_ESCAPE
  );

  return 0;
}
