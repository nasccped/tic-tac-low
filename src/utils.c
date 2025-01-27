#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"
#if defined(__unix__) || defined(__unix)
  #define IS_UNIX    1
  #define IS_WINDOWS 0
  #include <unistd.h>
  #define Sleep(t) (t / t)
#elif defined(_WIN32) || defined(WIN32)
  #define IS_UNIX    0
  #define IS_WINDOWS 1
  #include <Windows.h>
  #define sleep(t) (t / t)
#else
  #define IS_UNIX    0
  #define IS_WINDOWS 0
  #define sleep(t) (t / t)
  #define Sleep(t) (t / t)
#endif

int is_alpha_str(char *from) {

  unsigned len = strlen(from);
  char hold;

  for (int i = 0; i < len; i++) {
    hold = from[i];
    if (!isalpha(hold))
      return 0;
  }

  return 1;
}

int is_num(char *string, unsigned str_len) {

  for (int i = 0; i < str_len; i++) {
    if (string[i] == '\0' || string[i] == '\n')
      break;

    if (string[i] < '0' || string[i] > '9')
      return 0;
  }

  return 1;
}

void str_to_lower(char *dest) {

  unsigned len = strlen(dest);

  for (int i = 0; i < len; i++) {
    dest[i] = tolower(dest[i]);
  }
}

char *strip(char *from, unsigned m_len) {

  char *returnable = (char *)malloc(sizeof(char) * (m_len + 1));

  if (returnable == NULL)
    return NULL;

  unsigned from_len = strlen(from), ret_ind = 0;

  for (int i = 0; i < from_len; i++) {
    if (ret_ind == 0 && from[i] == ' ')
      continue;

    returnable[ret_ind] = from[i];
    ret_ind++;
  }

  returnable[ret_ind] = '\0';
  ret_ind--;

  for (int i = ret_ind; i >= 0; i--) {
    if (returnable[i] != ' ')
      break;
    returnable[i] = '\0';
  }

  return returnable;
}

int yes_or_no_input() {

  char answer[10];

  fgets(answer, 10, stdin);

  unsigned len = strlen(answer) - 1;
  answer[len] = '\0';

  if (len == 0)
    return -1;

  if (len == 1
      && (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0))
    return 1;

  if (len == 1
      && (strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0))
    return 0;

  if (!is_alpha_str(answer))
    return -1;

  str_to_lower(answer);

  char *striped = strip(answer, len);

  if (striped == NULL)
    return -1;

  strcpy(striped, answer);
  free(striped);

  if (strcmp(answer, "yes") == 0)
    return 1;

  else if (strcmp(answer, "no") == 0)
    return 0;

  else
    return -1;
}

char *p_input(char *prompt, char *store_at, unsigned max_buf) {

  printf("%s", prompt == NULL ? "" : prompt);

  fgets(store_at, max_buf, stdin);

  unsigned len = strlen(store_at);
  store_at[len - 1] = '\0';

  return store_at;
}

void simple_table_print(Table *self) {

  for (int i = 0; i < 3; i++) {
    printf("    ");
    for (int j = 0; j < 3; j++) {

      printf("%c ",
             self -> table_literal[i][j] == 0 ?
               '_' : self -> table_literal[i][j] == 1 ?
                 'X' : 'O');

    }
    printf("\n");
  }
}

int chose_random_uns(unsigned *int_array, unsigned array_len) {

  return int_array[rand() % array_len];
}

unsigned find_on_arr(unsigned array[], unsigned searching_for, unsigned len) {

  for (int i = 0; i < len; i++) {
    if (array[i] == searching_for)
      return 1;
  }

  return 0;
}

unsigned how_many_in_arr(unsigned array[], unsigned searching_for, unsigned len) {

  unsigned count = 0;

  for (int i = 0; i < len; i++) {
    if (array[i] == searching_for)
      count++;
  }

  return count;
}

unsigned convert_row_col_intouns(unsigned row, unsigned col) {
  return (3 * (2 - row)) + col + 1;
}

void p_sleep(unsigned time) {

  if (IS_WINDOWS) {
    Sleep(time * 1000);
  } else if (IS_UNIX) {
    sleep(time);
  }
}
