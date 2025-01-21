#ifndef _GAME_LITERAL_H
#define _GAME_LITERAL_H

#define MESSAGE_MAX_LEN 150

typedef enum MessageType {
  OK_AWAITING           ,
  OK_WINS               ,
  OK_BREAK_EVEN         ,
  ERR_OUT_OF_RANGE      ,
  ERR_NON_NUMERIC       ,
  ERR_CELL_ALREADY_TAKEN
} MessageType;

typedef struct GameMessage {
  MessageType type;
  char message[MESSAGE_MAX_LEN];
  void (*updated)(struct GameMessage *,
                  MessageType         ,
                  char *              );
} GameMessage;

void player_vs_player_game();
void player_vs_bot_game();

void update_game_message(struct GameMessage *, MessageType, char *);

static GameMessage MAIN_GAME_MESSAGE = {
  OK_AWAITING,
  "awaiting",
  &update_game_message
};

#endif
