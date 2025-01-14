#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tests.h"
#include "../include/game/player.h"
#include "../include/utils.h"

struct ArgMapping ARG_MAPPING = {
  0, NULL, &append_lhm
};

void TABLE_FUNC() {

  printf("\n");
  printf("  Let's run some table checking tests\n\n");
  printf("\n");

  unsigned r, c;

  for (int v = 1; v <= 9; v++) {

    set_player_move(&CATCH_PLAYER_MOVE, 1, v);

    r = CATCH_PLAYER_MOVE.at_row;
    c = CATCH_PLAYER_MOVE.at_col;

    printf("  Current player move:\n");

    for (int i = 0; i < 3; i++) {

      if (i == 1)
        printf("  > val: %d  ", v);
      else
        printf("            ");

      for (int j = 0; j < 3; j++) {

        if (r == i && c == j)
          printf("X ");
        else
          printf("_ ");

      }

      printf("\n");
    }
    printf("\n");
  }
}

void TAKE_POS_FUNC() {

  char val_holder[30];

  int val     ,
      row = -1,
      col = -1;

  while (1) {

    printf("\x1b[2J\x1b[H");

    printf("\n");
    printf("  row: %c | col: %c\n\n", row == -1 ? '?' : '0' + row,
                                      col == -1 ? '?' : '0' + col);

    printf("  Chose a pos by num keyboard (0 to quit): ");
    fgets(val_holder, 29, stdin);

    if (!is_num(val_holder, 30)) {
      row = -1;
      col = -1;
      continue;
    }

    val = atoi(val_holder);

    if (val == 0)
      break;

    if (CATCH_PLAYER_MOVE.get_move(&CATCH_PLAYER_MOVE,
                                   1                 ,
                                   val               ) == NULL) {
      row = -1;
      col = -1;
      continue;
    }

    row = CATCH_PLAYER_MOVE.at_row;
    col = CATCH_PLAYER_MOVE.at_col;
  }

}

void append_lhm(struct ArgMapping *self, struct LinkedHashMap *element) {

  if (self == NULL || element == NULL)
    return;

  element -> next = NULL;

  if (self -> count == 0) {
    self -> head = element;
    self -> count++;
    return;
  }

  struct LinkedHashMap *hold  = self -> head;

  for (int i = 0; i < (self -> count) - 1; i++) {
    hold = hold -> next;
  }

  hold -> next = element;
  self -> count++;
}

int main_test(char *arg) {
  
  struct ArgMapping *map = &ARG_MAPPING;

  map -> append(map, &TABLE   );
  map -> append(map, &TAKE_POS);

  struct LinkedHashMap *holder = map -> head;

  printf("\n");

  while (holder != NULL) {

    if (strcmp(arg, holder -> arg) == 0) {

      holder->func();
      printf("\n");

      return 0;
    }

    holder = holder -> next;
  }

  printf("The given arg (%s) could not be found!", arg);
  printf("\n");

  return 1;
}
