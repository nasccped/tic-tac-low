#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/const_vars.h"
#include "../include/game/bot.h"
#include "../include/game/player.h"
#include "../include/game/game_literal.h"
#include "../include/game/table.h"
#include "../include/tests.h"
#include "../include/utils.h"
#include "../include/visuals.h"

ArgMapping ARG_MAPPING = {
  0, NULL, &append_lhm
};

void TABLE_FUNC() {

  printf("\n");
  printf("  Let's run some table checking tests\n");
  printf("\n");
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
    printf("  row: %c | col: %c\n",
           row == -1 ? '?' : '0' + row,
           col == -1 ? '?' : '0' + col);
    printf("\n");

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
                                   1,
                                   val) == NULL) {
      row = -1;
      col = -1;
      continue;
    }

    row = CATCH_PLAYER_MOVE.at_row;
    col = CATCH_PLAYER_MOVE.at_col;
  }

}

void CHANGE_TABLE_FUNC() {

  Table *table = &MAIN_TABLE;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;

  int target_pos,
      table_situation = table -> check_for_victory(table);

  char input[INPUT_MAX_LEN],
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
                input,
                INPUT_MAX_LEN) == NULL) {

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

void PVB_GAME_FUNC() {

  clear_terminal();

  printf("\n");
  printf("  Did you want to enable color escapes? (yes/no)\n");
  printf("  > ");

  int colors = yes_or_no_input();

  // calling the function
  gameplay_function(colors > 0 ? 1 : 0, 1);
}

void RAND_FROM_ARRAY_FUNC() {

  unsigned int_array[] = {
     1,  2,  3,  4,  5,  6,
     7,  8,  9, 10, 20, 30,
    40, 50, 60, 70, 80, 90
  };

  unsigned len = 18;

  printf("  Our current array is:\n    ");

  for (int i = 0; i < len; i++) {
    printf("%d%s",
           int_array[i], i == len - 1 ?
           "." : ", ");
  }

  printf("\n\n  Let's chose a random number from it!\n");

  int the_chosen_one;

  for (int i = 0; i < 10; i++) {

    the_chosen_one = chose_random_uns(int_array, len);

    printf("    Choosing for the %s%dº time, val: %d\n",
           i < 9 ? " " : "",
           i + 1,
           the_chosen_one);
  }
}

void CONVERT_ROWCOLUNS_FUNC() {

  unsigned array_pair[9][2] = {
    {0, 0}, {0, 1}, {0, 2}, 
    {1, 0}, {1, 1}, {1, 2}, 
    {2, 0}, {2, 1}, {2, 2}, 
  }, row, col;

  printf("  Converting values:\n\n");
  printf("  row | colum | result\n");

  for (int i = 0; i < 9; i++) {
    row = array_pair[i][0];
    col = array_pair[i][1];
    printf("  %d   | %d     | %d\n",
           row, col, convert_row_col_intouns(row, col));
  }
}

void SLEEP_FUNC() {

  char input[10]     ,
       alert[50] = "";

  unsigned sleep_time;

  while (1) {

    clear_terminal();

    printf("\n");
    printf("  %s\n", alert);
    printf("\n");
    printf("  How many do you want to sleep? ('quit' to stop)\n");
    p_input("  > ", input, 10);

    if (strcmp(input, "quit") == 0) {
      break;
    }

    if (!is_num(input, strlen(input))) {
      strcpy(alert, "Your input isn't a number!");
      continue;
    }

    sleep_time = atoi(input);

    if (sleep_time > 20) {
      strcpy(alert, "20 seconds is the maximum sleep time allowed");
      continue;
    }

    printf("  Sleeping for %d seconds...\n", sleep_time);
    p_sleep(sleep_time);
  }

  printf("\n");
  printf("  Let's wake up!\n");
}

void TABLE_STATUS_FUNC() {

  Table *tb = &MAIN_TABLE;
  CatchPlayerMove *cpm = &CATCH_PLAYER_MOVE;
  Bot *bot = &MAIN_BOT;
  int expected_status_result = -1;
  unsigned expected_bot_moves[2] = {8, 2};
  unsigned bot_move;

  unsigned table1[3][3] = {
    {1, 1, 2},
    {0, 2, 0},
    {1, 2, 1}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cpm -> get_move(cpm, table1[i][j], convert_row_col_intouns(i, j));
      tb  -> change_on_table(tb, cpm);
    }
  }

  // Test 1
  if (tb -> check_for_victory(tb) != expected_status_result) {

    simple_table_print(tb);
    printf("\n");

    printf("  Test 1 - ERROR..table result returned an unexpected value:\n");
    printf("  expecting: %d\n", expected_status_result);
    printf("  received: %d\n", tb -> check_for_victory(tb));
    return;
  }

  unsigned table2[3][3] = {
    {1, 0, 2},
    {2, 1, 1},
    {1, 0, 2},
  };

  tb -> reset_table(tb);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cpm -> get_move(cpm, table2[i][j], convert_row_col_intouns(i, j));
      tb  -> change_on_table(tb, cpm);
    }
  }

  bot_move = bot -> get_move_pos(bot, tb);

  // Test 2
  if (!find_on_arr(expected_bot_moves, bot_move, 2)) {

    simple_table_print(tb);
    printf("\n");

    printf("  Test 2 - ERROR..bot has choosen an unexpected move:\n");
    printf("  expecting: any value in [ ");
    for (int i = 0; i < 2; i++)
      printf("%d ", expected_bot_moves[i]);
    printf("]\n");

    printf("  received: %d\n", bot_move);
    return;
  }

  printf("  Tests passed. Everything is OK!\n");
}

void append_lhm(ArgMapping *self, LinkedHashMap *element) {

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

int main_test(char *args[], int len) {
  
  if (len > 2) {
    // printing unexpected arg count
    printf("\n");
    printf("  Unexpected args being received (count: %d)\n", len - 1);

    // max argc count hint
    printf("\n");
    printf("  Maximum expected: 1\n");
    printf("\n");

    // printing each arg
    for (int i = 1; i < len; i++) {
      printf("  . %s\n", args[i]);
    }

    return 1;
  }

  char *test_call = args[1];
  ArgMapping *map = &ARG_MAPPING;

  map -> append(map, &TABLE);
  map -> append(map, &TAKE_POS);
  map -> append(map, &CHANGE_TABLE);
  map -> append(map, &PVP_GAME);
  map -> append(map, &PVB_GAME);
  map -> append(map, &RAND_FROM_ARRAY);
  map -> append(map, &CONVERT_ROWCOLUNS);
  map -> append(map, &SLEEP);
  map -> append(map, &TABLE_STATUS);

  LinkedHashMap *holder = map -> head;

  printf("\n");

  while (holder != NULL) {

    if (strcmp(test_call, holder -> arg) == 0) {
      holder -> func();
      return 0;
    }
    holder = holder -> next;
  }

  holder = map -> head;

  printf("  The given arg (%s) could not be found!\n", test_call);
  printf("  Available args are: \n");

  for (int i = 0; i < (map -> count); i++) {
    printf("    > %s\n", holder -> arg);
    holder = holder -> next;
  }

  printf("\n");

  return 1;
}
