#include "./headers/utils.h"

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _CTYPE_H
#include <ctype.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

int is_alpha_str(char *from) {

  unsigned len = strlen(from);
  int hold;

  for (int i = 0; i < len; i++) {
    hold = from[i];
    if (!isalpha(hold))
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

  if (len == 1 && (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0))
    return 1;

  if (len == 1 && (strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0))
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
