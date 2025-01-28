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

// starting the ArgMapping variables
ArgMapping ARG_MAPPING = {
  NULL, &append_lhm
};

/*
 * A function to the Table struct implementation
 *
 * It will loop in all possible positions (1..9) and update the
 * CatchPlayerMove's values, then these values will be catched
 * and printed in a fancy way
 * */
void TABLE_FUNC() {

  printf("\n");
  printf("  Let's run some table checking tests\n");
  printf("\n");
  printf("\n");

  unsigned r, c;

  // looping
  for (int v = 1; v <= 9; v++) {

    // changing the CatchPlayerMove struct values by it's function
    set_player_move(&CATCH_PLAYER_MOVE, 1, v);

    // getting the values
    r = CATCH_PLAYER_MOVE.at_row;
    c = CATCH_PLAYER_MOVE.at_col;

    printf("  Current player move:\n");

    // printing the values as a table
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

/*
 * A function to test the users input and convert it to col/row pair
 * */
void TAKE_POS_FUNC() {

  char val_holder[30];

  int val = -1,
      row = -1,
      col = -1;

  // while val isn't 0
  while (val) {

    clear_terminal();

    // print row and col value
    printf("\n");
    printf("  row: %c | col: %c\n",
           row == -1 ? '?' : '0' + row,
           col == -1 ? '?' : '0' + col);
    printf("\n");

    // asking for a position
    printf("  Chose a pos by num keyboard (0 to quit): ");
    fgets(val_holder, 29, stdin);

    // if given pos isn't a number
    if (!is_num(val_holder, strlen(val_holder))) {
      row = -1;
      col = -1;
      continue;
    }

    // convert input to int
    val = atoi(val_holder);

    // if invalid move
    if (CATCH_PLAYER_MOVE.get_move(&CATCH_PLAYER_MOVE,
                                   1,
                                   val) == NULL) {
      row = -1;
      col = -1;
      continue;
    }

    // else, update value
    row = CATCH_PLAYER_MOVE.at_row;
    col = CATCH_PLAYER_MOVE.at_col;
  }

}

/*
 * A function to test the table cells change like a game preview
 * */
void CHANGE_TABLE_FUNC() {

  // catch pointer with alias
  Table *table = &MAIN_TABLE;
  CatchPlayerMove *p_move = &CATCH_PLAYER_MOVE;

  // start variables
  int target_pos,
      table_situation = table -> check_for_victory(table);

  // input storer
  char input[INPUT_MAX_LEN],
       alert[40] = "Awaiting input";

  while (table_situation < 0) {

    // clear terminal + print visuals
    clear_terminal();
    printf("\n");
    printf("  Alert: %s\n", alert);
    printf("  ------------------\n");
    simple_table_print(table);
    printf("\n");

    // ask for position
    p_input("  Give some number ('quit!' to stop): ",
            input,
            INPUT_MAX_LEN);

    // if isn't numeric
    if (!is_num(input, strlen(input))) {
      strcpy(alert, "Given value isn't a numeric (1..9)");
      continue;
    }

    // convert input into int
    target_pos = atoi(input);

    // if invalid input
    if (p_move -> get_move(p_move, 1, target_pos) == NULL) {
      strcpy(alert, "Your input is out of range (1..9)");
      continue;
    }

    // if cell already taken
    if (!table -> change_on_table(table, p_move)) {
      strcpy(alert, "This pos is already taken");
      continue;
    }

    // else, update
    strcpy(alert, "Awaiting input");
    table_situation = table -> check_for_victory(table);
  }

  // print visuals before quit
  clear_terminal();
  printf("\n");
  printf("  Alert: %s\n", alert);
  printf("  ------------------\n");
  simple_table_print(table);
  printf("\n");
}

/*
 * A function 'straight to the point' about player vs player game
 * */
void PVP_GAME_FUNC() {

  // print visuals + catch color trigger
  clear_terminal();
  printf("\n");
  printf("  Did you want to enable color escapes? (yes/no)\n");
  printf("  > ");

  int colors = yes_or_no_input();

  // calling the function
  gameplay_function(colors > 0 ? 1 : 0, 0);
}

/*
 * A function 'straight to the point' about player vs bot game
 * */
void PVB_GAME_FUNC() {

  // print visuals + catch color trigger
  clear_terminal();
  printf("\n");
  printf("  Did you want to enable color escapes? (yes/no)\n");
  printf("  > ");

  int colors = yes_or_no_input();

  // calling the function
  gameplay_function(colors > 0 ? 1 : 0, 1);
}

/*
 * A function to test the personal made rand function
 * */
void RAND_FROM_ARRAY_FUNC() {

  // preparing an int collection
  unsigned int_array[] = {
     1,  2,  3,  4,  5,  6,
     7,  8,  9, 10, 20, 30,
    40, 50, 60, 70, 80, 90
  };

  unsigned len = 18;

  // print the entire array
  printf("  Our current array is:\n    ");

  for (int i = 0; i < len; i++) {
    printf("%d%s",
           int_array[i], i == len - 1 ?
           "." : ", ");
  }

  printf("\n\n  Let's chose a random number from it!\n");

  int the_chosen_one;

  // chose and print a random number 10 times
  for (int i = 0; i < 10; i++) {

    the_chosen_one = chose_random_uns(int_array, len);

    printf("    Choosing for the %s%dº time, val: %d\n",
           i < 9 ? " " : "",
           i + 1,
           the_chosen_one);
  }
}

/*
 * A function to test the int pair conversion into an unsinged
 * num. keyb. position
 * */
void CONVERT_ROWCOLUNS_FUNC() {

  // preparing pairs for each possible position (9 | 3x3)
  unsigned array_pair[9][2] = {
    {0, 0}, {0, 1}, {0, 2}, 
    {1, 0}, {1, 1}, {1, 2}, 
    {2, 0}, {2, 1}, {2, 2}, 
  }, row, col; // + row and col

  // printing table header
  printf("  Converting values:\n\n");
  printf("  row | colum | result\n");

  // looping, getting pair, converting and printing each result
  for (int i = 0; i < 9; i++) {
    row = array_pair[i][0];
    col = array_pair[i][1];
    printf("  %d   | %d     | %d\n",
           row,
           col,
           convert_row_col_intouns(row, col));
  }
}

/*
 * A function to test the personal cross-plataform sleep function
 * */
void SLEEP_FUNC() {

  // storing chars for response and alert
  char input[10]     ,
       alert[50] = "";

  unsigned sleep_time;

  // inf. (breakable) loop
  while (1) {

    // clear terminal, printing alert and asking for sleep time
    clear_terminal();
    printf("\n");
    printf("  %s\n", alert);
    printf("\n");
    printf("  How many do you want to sleep? ('quit' to stop)\n");
    p_input("  > ", input, 10);

    // if 'quit' called
    if (strcmp(input, "quit") == 0) {
      break;
    }

    // if input isn't numeric
    if (!is_num(input, strlen(input))) {
      strcpy(alert, "Your input isn't a number!");
      continue;
    }

    // update by input
    sleep_time = atoi(input);

    // if too long
    if (sleep_time > 20) {
      strcpy(alert, "20 seconds is the maximum sleep time allowed");
      continue;
    }

    // else, sleep
    printf("  Sleeping for %d seconds...\n", sleep_time);
    p_sleep(sleep_time);
  }

  printf("\n");
  printf("  Let's wake up!\n");
}

/*
 * A function to test if struct functions are returning expected
 * values
 * */
void TABLE_STATUS_FUNC() {

  // catching struct pointers by alias
  Table *tb = &MAIN_TABLE;
  CatchPlayerMove *cpm = &CATCH_PLAYER_MOVE;
  Bot *bot = &MAIN_BOT;

  // starting expected
  int expected_status_result = -1;
  unsigned expected_bot_moves[2] = {8, 2};

  unsigned bot_move;

  // a table sample
  unsigned table1[3][3] = {
    {1, 1, 2},
    {0, 2, 0},
    {1, 2, 1}
  };

  // update Table struct
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cpm -> get_move(cpm, table1[i][j], convert_row_col_intouns(i, j));
      tb  -> change_on_table(tb, cpm);
    }
  }

  // Test 1: table status testing
  if (tb -> check_for_victory(tb) != expected_status_result) {

    simple_table_print(tb);
    printf("\n");

    printf("  Test 1 - ERROR..table result returned an unexpected value:\n");
    printf("  expecting: %d\n", expected_status_result);
    printf("  received: %d\n", tb -> check_for_victory(tb));
    return;
  }

  // another table sample
  unsigned table2[3][3] = {
    {1, 0, 2},
    {2, 1, 1},
    {1, 0, 2},
  };

  // reset the pointer
  tb -> reset_table(tb);

  // update
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cpm -> get_move(cpm, table2[i][j], convert_row_col_intouns(i, j));
      tb  -> change_on_table(tb, cpm);
    }
  }

  bot_move = bot -> get_move_pos(bot, tb);

  // Test 2: bot move choice test
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

  // if all tests passed
  printf("  Tests passed. Everything is OK!\n");
}

/*
 * A function to append A LinkedHashMap struct (command option) to
 * the ArgMapping struct (works like an linked list)
 *
 * Input:
 *    - ArgMapping struct pointer (self)
 *    - LinkedHashMap struct pointer (element)
 * */
void append_lhm(ArgMapping *self, LinkedHashMap *element) {

  // update the next element pointer (initialy pointing to himself)
  // to NULL
  element -> next = NULL;

  // if LinkedList has 0 elements
  if (self -> head == NULL) {
    self -> head = element;
    return;
  }

  // else, hold the first, one
  LinkedHashMap *hold  = self -> head;

  // while the next isn't empty, catch they
  while (hold -> next != NULL) {
    hold = hold -> next;
  }

  // updates the next + increase count
  hold -> next = element;
}

/*
 * Main test function. It will append all test cases to the
 * 'Linked List' and call your test case (if it exists)
 *
 * Input:
 *    - string array <char pointer array> (args)
 *    - int val (len)
 *
 * Output:
 *    Integer value, 0 if the test case was called, 1 if something
 *    went wrong (arg length or test case not found)
 * */
int main_test(char *args[], int len) {
  
  // more than 1 arg was given
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

  // catching the test case call + ArgMapping alias
  char *test_call = args[1];
  ArgMapping *map = &ARG_MAPPING;

  // appending each node to the map pointer
  map -> append(map, &TABLE);
  map -> append(map, &TAKE_POS);
  map -> append(map, &CHANGE_TABLE);
  map -> append(map, &PVP_GAME);
  map -> append(map, &PVB_GAME);
  map -> append(map, &RAND_FROM_ARRAY);
  map -> append(map, &CONVERT_ROWCOLUNS);
  map -> append(map, &SLEEP);
  map -> append(map, &TABLE_STATUS);

  // catching the firs one
  LinkedHashMap *holder = map -> head;

  printf("\n");

  // finding test case on List
  while (holder != NULL) {

    // if found
    if (strcmp(test_call, holder -> arg) == 0) {
      holder -> func();
      return 0;
    }

    // else, point to the next
    holder = holder -> next;
  }

  // move back to the head
  holder = map -> head;

  // print alert
  printf("  The given arg (%s) could not be found!\n", test_call);
  printf("  Available args are: \n");

  // print each test case
  while (holder != NULL) {
    printf("    > %s\n", holder -> arg);
    holder = holder -> next;
  }

  printf("\n");

  // return error
  return 1;
}
