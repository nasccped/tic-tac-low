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
  void (*append)(struct ArgMapping    *,
                 struct LinkedHashMap *);
} ArgMapping;

void append_lhm(struct ArgMapping    *,
                struct LinkedHashMap *);

void TABLE_FUNC();
void TAKE_POS_FUNC();
void CHANGE_TABLE_FUNC();
void PVP_GAME_FUNC();
void PVB_GAME_FUNC();
void RAND_FROM_ARRAY_FUNC();
void CONVERT_ROWCOLUNS_FUNC();
void SLEEP_FUNC();
void TABLE_STATUS_FUNC();

static LinkedHashMap TABLE = {
  "table"    ,
  &TABLE_FUNC,
  &TABLE
};

static LinkedHashMap TAKE_POS = {
  "take_pos"    ,
  &TAKE_POS_FUNC,
  &TAKE_POS
};

static LinkedHashMap CHANGE_TABLE = {
  "change_table"    ,
  &CHANGE_TABLE_FUNC,
  &CHANGE_TABLE
};

static LinkedHashMap PVP_GAME = {
  "pvp_game"    ,
  &PVP_GAME_FUNC,
  &PVP_GAME
};

static LinkedHashMap PVB_GAME = {
  "pvb_game"    ,
  &PVB_GAME_FUNC,
  &PVB_GAME
};

static LinkedHashMap RAND_FROM_ARRAY = {
  "rand_from_array"    ,
  &RAND_FROM_ARRAY_FUNC,
  &RAND_FROM_ARRAY
};

static LinkedHashMap CONVERT_ROWCOLUNS = {
  "convert_rowcoluns"    ,
  &CONVERT_ROWCOLUNS_FUNC,
  &CONVERT_ROWCOLUNS
};

static LinkedHashMap SLEEP = {
  "sleep"    ,
  &SLEEP_FUNC,
  &SLEEP
};

static LinkedHashMap TABLE_STATUS = {
  "table_status"    ,
  &TABLE_STATUS_FUNC,
  &TABLE_STATUS
};

extern ArgMapping ARG_MAPPING;

#endif
