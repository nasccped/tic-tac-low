/* ------------------------------------------------------------------
 *
 * main.c
 *
 *     file responsible for store the main task and / or the
 *     combination of all tasks
 * ----------------------------------------------------------------*/
#include <stdio.h>
#include "mods/headers/inputs.h"
#include <string.h>

char* get_user_response(void);

// main function
int main(int argc, char *argv[]) {

  // initialize an empty int variable
  int  number;
  char *response;

  printf("Say my name: ");

  response = get_user_response();

  if (strcmp(response, "Heisenberg") == 0) {

    char *sr_white = "\033[1;48;2;67;61;139m\033[1;38;2;249;228;0m";
    char *rest_inP = "\033[0m";

    printf("\n\n  %s LET HIM COOK %s\n\n", sr_white, rest_inP);

  } else {

    printf("\n\n pooOr namu -_-\n\n");
  }

  free(response);

  return 0;
}
