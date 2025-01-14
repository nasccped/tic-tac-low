#ifndef _TESTS_H
#define _TESTS_H

int main_test(char *);

struct LinkedHashMap {
  const char *arg;
  void (*func)();
  struct LinkedHashMap *next;
};

struct ArgMapping {
  unsigned count;
  struct LinkedHashMap *head;
  void (*append)(struct ArgMapping *, struct LinkedHashMap *);
};

void append_lhm(struct ArgMapping *, struct LinkedHashMap *);

void TABLE_FUNC();
void TAKE_POS_FUNC();

static struct LinkedHashMap TABLE = {
  "table",
  &TABLE_FUNC,
  &TABLE,
};

static struct LinkedHashMap TAKE_POS = {
  "take_pos",
  &TAKE_POS_FUNC,
  &TAKE_POS
};

extern struct ArgMapping ARG_MAPPING;

#endif
