#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

#ifndef _PLAYER_H_
#include "./mods/player.h"
#endif

#ifndef _VISUALS_H_
#include "./mods/visuals.h"
#endif

int main(int arc, char *argv[]) {

  clear_terminal();

  test_player();

  return 0;
}
