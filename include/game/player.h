#ifndef _PLAYER_H
#define _PLAYER_H

struct CatchPlayerMove {
  unsigned player_val,
           at_row    ,
           at_col    ;
};

static struct CatchPlayerMove CATCH_PLAYER_MOVE = {
  0, 0, 0
};

#endif
