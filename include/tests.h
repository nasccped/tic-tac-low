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
static struct LinkedHashMap TABLE = {
  "table",
  &TABLE_FUNC,
  &TABLE,
};

extern struct ArgMapping ARG_MAPPING;

#endif
