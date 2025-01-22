#ifndef _CONST_VARS_H
#define _CONST_VARS_H

#define INPUT_MAX_LEN 50

static const char *RESET_ESCAPE     = "\x1b[0m"   ,
                  *BOLD_RED_NONE    = "\x1b[1;31m",
                  *BOLD_GREEN_NONE  = "\x1b[1;32m",
                  *BOLD_YELLOW_NONE = "\x1b[1;33m",
                  *BOLD_BLUE_NONE   = "\x1b[1;34m",
                  *BOLD_WHITE_NONE  = "\x1b[1;37m";

extern unsigned ENABLE_COLORS;

#endif
