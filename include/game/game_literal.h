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
  void (*print_message)(struct GameMessage *, int);
  void (*update)(struct GameMessage * ,
                 MessageType          ,
                 char *               );
} GameMessage;

void gameplay_function(int, int);

void print_message(struct GameMessage *, int);
void update_game_message(struct GameMessage * ,
                         MessageType          ,
                         char *               );

static GameMessage MAIN_GAME_MESSAGE = {
  OK_AWAITING   ,
  "[NO MESSAGE]",
  &print_message,
  &update_game_message
};

#endif
