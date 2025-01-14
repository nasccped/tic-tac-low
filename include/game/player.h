#ifndef _PLAYER_H
#define _PLAYER_H

struct CatchPlayerMove {

  unsigned player_val,
           at_row    ,
           at_col    ;

  struct CatchPlayerMove *(*get_move)(struct CatchPlayerMove *,
                                     unsigned                ,
                                     unsigned                );
};

struct CatchPlayerMove *set_player_move(struct CatchPlayerMove *,
                                        unsigned                ,
                                        unsigned                );

static struct CatchPlayerMove CATCH_PLAYER_MOVE = {
  0, 0, 0, &set_player_move
};

#endif
