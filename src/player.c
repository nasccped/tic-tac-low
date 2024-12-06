#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

#include "./mods/player.h"

Player *new_player(char *name) {

  if (name == NULL)
    return NULL;

  if (strlen(name) > PLAYER_NAME_MAX_LEN - 1) {
    free(name);
    return NULL;
  }

  Player *malloced_player = (Player *)malloc(sizeof(Player));

  if (malloced_player == NULL) {
    free(name);
    return NULL;
  }

  strncpy(malloced_player->name, name, PLAYER_NAME_MAX_LEN - 1);
  free(name);

  malloced_player->points = 0;

  return malloced_player;
}

bool insert_player(PlayerList *self, Player *player) {

  if (player == NULL)
    return false;

  if (self == NULL) {
    free(player);
    return false;
  }

  int cur_index = self->current_lenght, max_size = self->max_length;

  if (cur_index == max_size) {
    free(player);
    return false;
  }

  self->list[cur_index] = player;
  self->current_lenght++;

  return true;
}

void destroy_player(Player *player) {

  if (player != NULL)
    free(player);
}

void destroy_player_list(PlayerList *list) {

  for (int i = 0; i < list->current_lenght; i++)
    destroy_player(list->list[i]);
}
