#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_NAME_MAX_LEN 30
#define PLAYER_LIST_MAX_SIZE 5

typedef struct Player {
  char name[PLAYER_NAME_MAX_LEN];
  unsigned points;
} Player;

typedef struct PlayerList {
  Player *list[PLAYER_LIST_MAX_SIZE];
  unsigned current_lenght, max_length;
  bool (*insert_player)(struct PlayerList *, Player *);
} PlayerList;

Player *new_player(char *name);
bool insert_player(PlayerList *self, Player *player);
void destroy_player(Player *player);
void destroy_player_list(PlayerList *list);

void test_player();

extern PlayerList PLAYER_LIST;

#endif
