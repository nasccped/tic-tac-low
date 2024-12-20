#ifndef _PLAYER_H_
#define _PLAYER_H_

// our constants to max lenght (list | player name)
#define PLAYER_LIST_MAX_SIZE 5  /**< Max size list supports          */
#define PLAYER_NAME_MAX_LEN  30 /**< Max length player name supports */

/**
 * @enum PLayerCreationStatus
 * @brief Values to return when trying to create a new Player pointer.
 *
 * Create a new Player pointer doesn't means exactly 'create'. The
 * pointer is created/malloced outside a function and passed as an
 * argument, so in this way, if the function fails, it can return the
 * fail reason instead a simple NULL pointer.
 */
typedef enum {
  PLAYER_CREATED      , /**< Player successfully created report                          */
  PLAYER_NAME_IS_EMPTY, /**< Empty name report                                           */
  PLAYER_NAME_OVERFLOW, /**< Name greater than expected (PLAYER_NAME_MAX_LEN - 1) report */
  PLAYER_NAME_IS_NULL , /**< Given name unexpectedly null report                         */
  PLAYER_IS_NULL      , /**< Given player pointer unexpectedly null report               */
} PlayerCreationStatus;


/**
 * @enum PlayerListStatus
 * @brief Values to return when trying to performe some action within
 *        our PlayerList variable.
 *
 * These values can be returned in a bunch of procedures, such as:
 *   - insert player
 *   - edit player
 *   - remove player
 *   - find player
 *
 * Each procedure have his own success/fail value(s) to return
 */
typedef enum PlayerListStatus {
  PLAYER_ADDED         , /**< Player successfully added report                                         */
  PLAYER_REMOVED       , /**< Player successfully removed report                                       */
  PLAYER_EDITED        , /**< Player successfully edited report                                        */
  PLAYER_FOUND         , /**< Player successfully found report                                         */
  LIST_IS_FULL         , /**< Player couldn't be added to list (because it's full) report              */
  PLAYER_ALREADY_EXISTS, /**< Trying to add a player that is already on list (query by name) report    */
  PLAYER_NOT_FOUND     , /**< Player n couldn't be get (n probably is out of list[range]) report       */
  LIST_IS_NULL         , /**< PlayerList unexpectedly null report                                      */
  NEW_NAME_IS_NULL     , /**< Given new name is unexpectedly null report                               */
  NEW_NAME_IS_EMPTY    , /**< Given new name is empty string (or only spaces too) report               */
  NEW_NAME_OVERFLOW    , /**< Given new name is greater than expected (PLAYER_NAME_MAX_LEN - 1) report */
} PlayerListStatus;

/**
 * @struct Player
 * */
typedef struct Player {
  char     name[PLAYER_NAME_MAX_LEN];
  unsigned points                   ;
} Player;

// function to put the name into Player pointer. It will return the status
// *dest is already malloced
PlayerCreationStatus new_player(Player *dest, char *name,
                                unsigned default_points);

// function to destroy player by getting the pointer
void destroy_player(Player *player);

void trim_player_name(char *dest, char *from, unsigned max_leng);

// struct to store the PlayerList variables and also some methods, like in OOP
typedef struct PlayerList {
  // the list itself
  Player *list[PLAYER_LIST_MAX_SIZE];

  unsigned current_lenght, // unsigned pairs (store current and limits)
      max_length;

  // functions (self-explanatory titles)
  PlayerListStatus (*insert)(struct PlayerList *, Player *);
  PlayerListStatus (*edit)(struct PlayerList *, unsigned, char *);
  PlayerListStatus (*remove)(struct PlayerList *, unsigned);
  PlayerListStatus (*find)(struct PlayerList *, struct Player **, unsigned);
  void (*destroy)(struct PlayerList *);
  void (*sort)(struct PlayerList *);
} PlayerList;

// insert player by taking pointer (list, player itself)
PlayerListStatus insert_player(struct PlayerList *self, Player *player);

// edit player name by getting values (list, index on the list, new name)
PlayerListStatus edit_player(struct PlayerList *self, unsigned index,
                             char *new_name);

// remove player from the list by the index
PlayerListStatus remove_player(struct PlayerList *self, unsigned index);

PlayerListStatus get_player(struct PlayerList *self, struct Player **dest, unsigned index);

// destroy all the player list by getting the reference
void destroy_player_list(struct PlayerList *self);

void sort_list_points(PlayerList *self);

void test_player();

extern PlayerList PLAYER_LIST;

#endif
