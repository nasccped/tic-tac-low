#ifndef _ROOMS_H
#define _ROOMS_H

typedef enum GameRoomEnum {
  MAIN_MENU,
  PLAYING  ,
  ABOUT    ,
  QUIT     ,
} GameRoom;

static GameRoom MAIN_GAME_ROOM;

#endif
