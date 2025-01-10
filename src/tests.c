#include "./headers/tests.h"

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

struct ArgMapping ARG_MAPPING = {
  0, NULL, &append_lhm
};

void TABLE_FUNC() {

  printf("  Let's print some tables?\n");

}

int main_test(char *arg) {
  
  struct ArgMapping *map = &ARG_MAPPING;

  map -> append(map, &TABLE);

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

  for (int i = 0; i < self -> count; i++) {
    hold = hold -> next;
  }

  hold -> next = element;
  self -> count++;
}
