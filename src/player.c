#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

#ifndef _PLAYER_H_
#include "./mods/player.h"
#endif

PlayerList PLAYER_LIST = {{}, 0, PLAYER_LIST_MAX_SIZE, &insert_player};

Player *new_player(char *name) {

  if (name == NULL)
    return NULL;

  if (strlen(name) > PLAYER_NAME_MAX_LEN - 1) {
    free(name);
    name = NULL;
    return NULL;
  }

  Player *malloced_player = (Player *)malloc(sizeof(Player));

  if (malloced_player == NULL) {
    free(name);
    name = NULL;
    return NULL;
  }

  strncpy(malloced_player->name, name, PLAYER_NAME_MAX_LEN - 1);
  free(name);
  name = NULL;

  malloced_player->points = 0;

  return malloced_player;
}

bool insert_player(PlayerList *self, Player *player) {

  if (player == NULL)
    return false;

  if (self == NULL) {
    free(player);
    player = NULL;
    return false;
  }

  int cur_index = self->current_lenght, max_size = self->max_length;

  if (cur_index == max_size) {
    free(player);
    player = NULL;
    return false;
  }

  self->list[cur_index] = player;
  self->current_lenght++;

  return true;
}

void destroy_player(Player *player) {

  if (player != NULL) {
    free(player);
    player = NULL;
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
  char *p_names[] = {"Mist", "Ash", "Brock", "Pikachu"};
  size_t p_names_len = sizeof(p_names) / sizeof(p_names[0]);

  // introduction...
  printf("\nLet's malloc 4 players names: ");

  // iterate through player literal names array
  for (int i = 0; i < p_names_len; i++) {
    printf("\033[1;33m%s\033[0m", p_names[i]);
    printf("%s", (i == p_names_len - 1) ? "" : ", ");
  }

  printf("\n\n");

  // malloc pointers
  char *pn_1 = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);
  char *pn_2 = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);
  char *pn_3 = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);
  char *pn_4 = (char *)malloc(sizeof(char) * PLAYER_NAME_MAX_LEN);

  // store them on array
  char *pn_array[] = {pn_1, pn_2, pn_3, pn_4};

  // copy literals to malloc pointers in array
  for (int i = 0; i < p_names_len; i++) {
    strncpy(pn_array[i], p_names[i], PLAYER_NAME_MAX_LEN);
  }

  // creating and puting players pointers in an array
  Player *p1, *p2, *p3, *p4;
  Player *p_array[] = {p1, p2, p3, p4};

  // creating each player pointer by name
  for (int i = 0; i < p_names_len; i++) {

    // if the current pointer generation returns NULL (fail)
    if ((p_array[i] = new_player(pn_array[i])) == NULL) {

      // print error
      printf("p%d malloc \033[1;31mfailed...\033[0m Terminating!\n", i + 1);

      // free all malloced names by starting on the next
      // the current one was already freed
      for (int j = i + 1; j < p_names_len; j++) {
        free(p_names[j]);
        p_names[j] = NULL;
      }

      // destroy each player malloced into the list
      destroy_player_list(&PLAYER_LIST);

      // terminate
      return;
    }

    // else, insert player on the list
    insert_player(&PLAYER_LIST, p_array[i]);

    // print success
    printf("p%d \033[1;32mhas been generated\033[0m and added to list! "
           "( \033[1;33m%s\033[0m )\n",
           i + 1, p_array[i]->name);
  }

  printf("\nSo now, let's iterate through our \033[1;34mlist of "
         "players\033[0m\n\n");

  // iterate
  for (int i = 0; i < PLAYER_LIST.current_lenght; i++) {

    // hold the current player by pointer
    Player *p_holder = PLAYER_LIST.list[i];

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

  printf("\n");

  // free them all
  destroy_player_list(&PLAYER_LIST);

  if (PLAYER_LIST.list[0] == NULL)
    printf("The list has been freed\n");
  else
    printf("There's some players yet?\n");
}
