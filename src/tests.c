#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/visuals.h"
#include "../include/game/table.h"
#include "../include/tests.h"
#include "../include/game/player.h"
#include "../include/utils.h"
#include "../include/const_vars.h"
#include "../include/game/game_literal.h"

ArgMapping ARG_MAPPING = {
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

void CHANGE_TABLE_FUNC() {

  Table           *table  = &MAIN_TABLE       ;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;

  int target_pos                                         ,
      table_situation = table -> check_for_victory(table);

  char input[INPUT_MAX_LEN]        ,
       alert[40] = "Awaiting input";

  while (1) {

    clear_terminal();

    printf("\n");
    printf("  Alert: %s\n", alert);
    printf("  ------------------\n");

    for (int i = 0; i < 3; i++) {
      printf("      ");

      for (int j = 0; j < 3; j++)
        printf("%c ", table -> table_literal[i][j] == 0 ? '-' : 'X');

      printf("\n");
    }

    printf("\n");

    if (table_situation == 1) {
      printf("  Player 1 wins!\n");
      break;
    }

    if (p_input("  Give some number ('quit!' to stop): ",
                input                               ,
                INPUT_MAX_LEN                       ) == NULL) {
      printf("  Your input has been returned NULL\n");
      break;
    }

    if (strcmp(input, "quit!") == 0) {
      printf("  Quitting...");
      break;
    }

    if (!is_num(input, strlen(input))) {
      strcpy(alert, "Given value isn't a numeric (1..9)");
      continue;
    }

    target_pos = atoi(input);

    if (p_move -> get_move(p_move, 1, target_pos) == NULL) {
      strcpy(alert, "Your input is out of range (1..9)");
      continue;
    }

    if (!table -> change_on_table(table, p_move)) {
      strcpy(alert, "This pos is already taken");
      continue;
    }

    strcpy(alert, "Awaiting input");
    table_situation = table -> check_for_victory(table);
  }
}

void PVP_GAME_FUNC() {

  clear_terminal();

  printf("\n");
  printf("  Did you want to enable color escapes? (yes/no)\n");
  printf("  > ");

  int colors = yes_or_no_input();

  // calling the function
  gameplay_function(colors > 0 ? 1 : 0, 0);
}

#include <time.h>

void RAND_FROM_ARRAY_FUNC() {

  unsigned int_array[] = {
     1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 20, 30, 40, 50, 60, 70, 80, 90
  };

  unsigned len = 18;

  printf("  Our current array is:\n    ");

  for (int i = 0; i < len; i++) {
    printf("%d%s", int_array[i], i == len - 1 ? "." : ", ");
  }

  printf("\n\n  Let's chose a random number from it!\n");

  srand(time(NULL));

  int the_chosen_one;

  for (int i = 0; i < 10; i++) {

    the_chosen_one = chose_random_uns(int_array, len);

    printf("    Choosing for the %s%dº time, val: %d\n",
           i < 9 ? " " : ""                            ,
           i + 1                                       ,
           the_chosen_one
    );
  }
}

void append_lhm(ArgMapping *self, LinkedHashMap *element) {

  if (self == NULL || element == NULL)
    return;

  element -> next = NULL;

  if (self -> count == 0) {
    self -> head = element;
    self -> count++;
    return;
  }

  LinkedHashMap *hold  = self -> head;

  for (int i = 0; i < (self -> count) - 1; i++) {
    hold = hold -> next;
  }

  hold -> next = element;
  self -> count++;
}

int main_test(char *arg) {
  
  ArgMapping *map = &ARG_MAPPING;

  map -> append(map, &TABLE            );
  map -> append(map, &TAKE_POS         );
  map -> append(map, &CHANGE_TABLE     );
  map -> append(map, &PVP_GAME         );
  map -> append(map, &RAND_FROM_ARRAY  );
  map -> append(map, &CONVERT_ROWCOLUNS);

  LinkedHashMap *holder = map -> head;

  printf("\n");

  while (holder != NULL) {

    if (strcmp(arg, holder -> arg) == 0) {

      holder->func();

      return 0;
    }

    holder = holder -> next;
  }

  holder = map -> head;

  printf("  The given arg (%s) could not be found!\n", arg);
  printf("  Available args are: \n");

  for (int i = 0; i < (map -> count); i++) {
    printf("    > %s\n", holder -> arg);
    holder = holder -> next;
  }

  printf("\n");

  return 1;
}
