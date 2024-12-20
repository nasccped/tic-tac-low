#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

#ifndef _VISUALS_H_
#include "./mods/visuals.h"
#endif

void clear_terminal() {
  printf("\033[H\033[2J");
}
