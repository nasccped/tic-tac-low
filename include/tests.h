#ifndef _TESTS_H
#define _TESTS_H

int main_test(char *);

typedef struct LinkedHashMap {
  const char *arg;
  void (*func)();
  struct LinkedHashMap *next;
} LinkedHashMap;

typedef struct ArgMapping {
  unsigned count;
  struct LinkedHashMap *head;
  void (*append)(struct ArgMapping *, struct LinkedHashMap *);
} ArgMapping;

void append_lhm(struct ArgMapping *, struct LinkedHashMap *);

void TABLE_FUNC();
void TAKE_POS_FUNC();
void CHANGE_TABLE_FUNC();

static LinkedHashMap TABLE = {
  "table",
  &TABLE_FUNC,
  &TABLE,
};

static LinkedHashMap TAKE_POS = {
  "take_pos",
  &TAKE_POS_FUNC,
  &TAKE_POS
};

static LinkedHashMap CHANGE_TABLE = {
  "change_table",
  &CHANGE_TABLE_FUNC,
  &CHANGE_TABLE
};

extern ArgMapping ARG_MAPPING;

#endif
