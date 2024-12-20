#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

#ifndef _PLAYER_H_
#include "./mods/player.h"
#endif

PlayerList PLAYER_LIST = {{},
                          0,
                          PLAYER_LIST_MAX_SIZE,
                          &insert_player,
                          &edit_player,
                          &remove_player,
                          &get_player,
                          &destroy_player_list,
                          &sort_list_points};

void trim_player_name(char *dest, char *from, unsigned int max_leng) {

  if (dest == NULL)
    return;

  if (from == NULL)
    return;

  if (strlen(from) > max_leng - 1)
    return;

  // store the current p_name index to change
  int p_name_index = 0;

  // for each char in the name
  for (int i = 0; i < strlen(from); i++) {

    // if current char is space and (previous char in p_name is also space, or
    // the p_name index is 0 (begin))
    if (from[i] == ' ' && (dest[p_name_index - 1] == ' ' || p_name_index == 0))
      continue; // goto next iter

    // else, change char
    dest[p_name_index] = from[i];

    // increment index
    p_name_index++;
  }

  // change last char to string-end
  dest[p_name_index] = '\0';
}

PlayerCreationStatus new_player(Player *dest, char *name,
                                unsigned default_points) {

  // dest is null (null player error)
  if (dest == NULL) {

    if (name != NULL)
      free(name);

    return PLAYER_IS_NULL;
  }

  // name is null (null player name error)
  if (name == NULL) {

    free(dest);

    return PLAYER_NAME_IS_NULL;
  }

  // name len > max (player name overflow error)
  if (strlen(name) > PLAYER_NAME_MAX_LEN - 1) {
    free(dest);
    free(name);
    return PLAYER_NAME_OVERFLOW;
  }

  // name len = 0 (player empty name error)
  if (strlen(name) == 0) {
    free(dest);
    free(name);
    return PLAYER_NAME_IS_EMPTY;
  }

  trim_player_name(dest->name, name, PLAYER_NAME_MAX_LEN);

  free(name);

  if (strlen(dest->name) == 0) {
    free(dest);
    return PLAYER_NAME_IS_EMPTY;
  }

  // setting the points
  dest->points = default_points;

  // returning success
  return PLAYER_CREATED;
}

PlayerListStatus insert_player(PlayerList *self, Player *player) {

  if (player == NULL) {
    destroy_player(player);
    return PLAYER_NOT_FOUND;
  }

  if (self == NULL) {
    destroy_player(player);
    return LIST_IS_NULL;
  }

  int cur_index = self->current_lenght, max_size = self->max_length;

  if (cur_index == max_size) {
    destroy_player(player);
    return LIST_IS_FULL;
  }

  self->list[cur_index] = player;
  self->current_lenght++;

  return PLAYER_ADDED;
}

PlayerListStatus edit_player(struct PlayerList *self, unsigned int index,
                             char *new_name) {
  if (self == NULL) {

    if (new_name != NULL)
      free(new_name);

    return LIST_IS_NULL;
  }

  if (new_name == NULL)
    return PLAYER_NOT_FOUND;

  if (index >= self->current_lenght)
    return PLAYER_NOT_FOUND;

  switch (strlen(new_name)) {
  case 0:
    free(new_name);
    return NEW_NAME_IS_EMPTY;

  case PLAYER_NAME_MAX_LEN - 1:
    free(new_name);
    return NEW_NAME_OVERFLOW;
  }

  char temp[30];

  trim_player_name(temp, new_name, PLAYER_NAME_MAX_LEN);

  if (strlen(temp) == 0)
    return NEW_NAME_IS_EMPTY;

  Player *player_holder = self->list[index];

  strcpy(player_holder->name, "");
  strncpy(player_holder->name, temp, PLAYER_NAME_MAX_LEN);

  return PLAYER_EDITED;
}

PlayerListStatus remove_player(struct PlayerList *self, unsigned index) {

  if (self == NULL)
    return LIST_IS_NULL;

  if (index >= self->current_lenght)
    return PLAYER_NOT_FOUND;

  free(self->list[index]);
  self->list[index] = NULL;

  for (int i = index + 1; i < self->current_lenght; i++) {
    self->list[i - 1] = self->list[i];
  }

  self->list[self->current_lenght] = NULL;
  self->current_lenght--;
  return PLAYER_REMOVED;
}

PlayerListStatus get_player(struct PlayerList *self, Player **dest,
                            unsigned index) {

  if (self == NULL)
    return LIST_IS_NULL;

  if (index >= self->current_lenght)
    return PLAYER_NOT_FOUND;

  if (self->list[index] == NULL)
    return PLAYER_NOT_FOUND;

  *dest = self->list[index];

  return PLAYER_FOUND;
}

void sort_list_points(PlayerList *self) {

  if (self == NULL)
    return;

  if (self->current_lenght == 0)
    return;

  Player *holder;

  for (int i = 1; i < self->current_lenght; i++) {
    if (self->list[i]->points > self->list[i - 1]->points) {
      holder = self->list[i];
      self->list[i] = self->list[i - 1];
      self->list[i - 1] = holder;
      i = 0;
    }
  }
}

void destroy_player(Player *player) {

  if (player != NULL) {
    free(player);
  }
}

void destroy_player_list(PlayerList *list) {

  for (int i = 0; i < list->current_lenght; i++) {
    destroy_player(list->list[i]);
    list->list[i] = NULL;
  }

  list->current_lenght = 0;
}

void test_player() {

  // test title
  printf("%sTesting the player.c(h) implementation!%s\n\n", "\033[1;34m",
         "\033[0m");

  // our literal names and array size
  char *player_name_literals[] = {"Mist", "Ash", "Brock", "Pikachu"};
  size_t pnl_len =
      sizeof(player_name_literals) / sizeof(player_name_literals[0]);

  // introduction...
  printf("\nLet's malloc 4 players names: ");

  // iterate through player literal names array
  for (int i = 0; i < pnl_len; i++) {
    printf("\033[1;33m%s\033[0m", player_name_literals[i]);
    printf("%s", (i == pnl_len - 1) ? "" : ", ");
  }

  printf("\n\n");

  // store them on array
  char *player_name_mallocs[pnl_len];

  // copy literals to malloc pointers in array
  for (int i = 0; i < pnl_len; i++) {

    player_name_mallocs[i] = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);

    strncpy(player_name_mallocs[i], player_name_literals[i],
            PLAYER_NAME_MAX_LEN);
  }

  // creating and puting players pointers in an array
  Player *players_array[4];

  // creating each player pointer by name
  for (int i = 0; i < pnl_len; i++) {

    players_array[i] = (Player *)malloc(sizeof(Player));

    // if the current pointer generation returns NULL (fail)
    if (new_player(players_array[i], player_name_mallocs[i], (i % 3) * 2) !=
        PLAYER_CREATED) {

      // print error
      printf("Player %d generation \033[1;31mfailed...\033[0m Terminating!\n",
             i + 1);

      // free all malloced names by starting on the next
      // the current one was already freed
      for (int j = i + 1; j < pnl_len; j++)
        free(player_name_mallocs[j]);

      // destroy each player malloced into the list
      PLAYER_LIST.destroy(&PLAYER_LIST);

      // terminate
      return;
    }

    // else, insert player on the list
    if (insert_player(&PLAYER_LIST, players_array[i]) != PLAYER_ADDED) {

      printf("\033[1;31mSomething went wrong\033[0m when trying to add Player "
             "%d to the list!\n",
             i + 1);

      printf("Terminating...\n");

      for (int j = i + 1; j < pnl_len; j++)
        free(player_name_mallocs[j]);

      PLAYER_LIST.destroy(&PLAYER_LIST);
    }

    // print success
    printf("Player %d \033[1;32mhas been generated\033[0m and added to list! "
           "( \033[1;33m%s\033[0m )\n",
           i + 1, players_array[i]->name);
  }

  printf("\n\nCurrent list status: (len: \033[1;32m%d\033[0m | max: "
         "\033[1;31m%d\033[0m)\n",
         PLAYER_LIST.current_lenght, PLAYER_LIST.max_length);

  printf("\nSo now, let's iterate through our \033[1;34mlist of "
         "players\033[0m\n\n");

  Player *p_holder;

  // iterate
  for (int i = 0; i < PLAYER_LIST.current_lenght; i++) {

    // hold the current player by pointer
    p_holder = PLAYER_LIST.list[i];

    // show name
    printf("   Player \033[1;32mn%d:\033[1;33m %s\033[0m", i + 1,
           p_holder->name);

    // gap spaces
    for (int j = strlen(p_holder->name); j < 20; j++)
      printf(" ");

    // show points
    printf("| %d point(s)\n", p_holder->points);

    p_holder++;
  }

  PLAYER_LIST.sort(&PLAYER_LIST);

  printf("\n\nSame list after \033[1;34msorting\033[0m:\n\n");

  for (int i = 0; i < PLAYER_LIST.current_lenght; i++) {

    // hold the current player by pointer
    p_holder = PLAYER_LIST.list[i];

    // show name
    printf("   Player \033[1;32mn%d:\033[1;33m %s\033[0m", i + 1,
           p_holder->name);

    // gap spaces
    for (int j = strlen(p_holder->name); j < 20; j++)
      printf(" ");

    // show points
    printf("| %d point(s)\n", p_holder->points);

    p_holder++;
  }

  unsigned ind = 3;
  Player *get;
  char *player_new_name = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);
  strncpy(player_new_name, "Charizard", PLAYER_NAME_MAX_LEN - 1);

  if (PLAYER_LIST.find(&PLAYER_LIST, &get, ind) != PLAYER_FOUND) {

    printf("\n\033[1;31mSomething went wrong\033[0m when trying to get Player "
           "%d!\n\n",
           ind + 1);

    printf("Terminating\n\n");

    PLAYER_LIST.destroy(&PLAYER_LIST);

    return;
  }

  printf("\n\nLet's change the Player %d name (%s) to \033[1;33m%s\033[0m\n",
         ind + 1, get->name, player_new_name);

  if (PLAYER_LIST.edit(&PLAYER_LIST, ind, player_new_name) != PLAYER_EDITED) {

    printf(
        "\n\033[1;31mSomething went wrong\033[0m when trying to change Player "
        "%d (%s)!\n\n",
        ind + 1, get->name);

    printf("Terminating\n\n");

    PLAYER_LIST.destroy(&PLAYER_LIST);

    return;
  }

  printf("\nOur list now:\n");

  for (int i = 0; i < PLAYER_LIST.current_lenght; i++) {

    // hold the current player by pointer
    p_holder = PLAYER_LIST.list[i];

    // show name
    printf("   Player \033[1;32mn%d:\033[1;33m %s\033[0m", i + 1,
           p_holder->name);

    // gap spaces
    for (int j = strlen(p_holder->name); j < 20; j++)
      printf(" ");

    // show points
    printf("| %d point(s)\n", p_holder->points);

    p_holder++;
  }

  ind = 1;

  PLAYER_LIST.find(&PLAYER_LIST, &get, ind);

  printf("\nAnd now, let's \033[1;31mremove\033[0m Player %d "
         "(\033[1;33m%s\033[0m) from our list!\n",
         ind + 1, get->name);

  PLAYER_LIST.remove(&PLAYER_LIST, ind);

  printf("\nOur list now:\n");

  for (int i = 0; i < PLAYER_LIST.current_lenght; i++) {

    // hold the current player by pointer
    p_holder = PLAYER_LIST.list[i];

    // show name
    printf("   Player \033[1;32mn%d:\033[1;33m %s\033[0m", i + 1,
           p_holder->name);

    // gap spaces
    for (int j = strlen(p_holder->name); j < 20; j++)
      printf(" ");

    // show points
    printf("| %d point(s)\n", p_holder->points);

    p_holder++;
  }

  printf("\n\n");

  // free them all
  PLAYER_LIST.destroy(&PLAYER_LIST);

  if (PLAYER_LIST.list[0] == NULL)
    printf("The list has been freed\n");
  else
    printf("There's some players yet?\n");
}
