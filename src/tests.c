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

#ifndef _TABLE_H
#include "./headers/game/table.h"
#endif

struct ArgMapping ARG_MAPPING = {
  0, NULL, &append_lhm
};

void TABLE_FUNC() {

  printf("\n");
  printf("  Let's run some table checking tests\n\n");
  printf("\n");

  struct Table *table_collec[] = {
    &tab_test1,
    &tab_test2,
    &tab_test3,
    &tab_test4,
  };
  
  int expected_result[4] = {
    1,
    2,
    0,
    -1
  };

  int results[4];

  for (int i = 0; i < 4; i++) {

    results[i] = table_collec[i] -> check_for_victory(table_collec[i]);
  }

  for (int i = 0; i < 4; i++) {

    printf("  Testing nº%d\n", i + 1);
    printf("  Expected result: %d\n", expected_result[i]);
    printf("  Founded result: %d\n", results[i]);

    if (i < 3)
      printf("\n  ---------------------------------\n");

    printf("\n");
  }

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
