#include "./headers/visuals.h"

#ifndef _STDIO_H_
#include <stdio.h>
#endif

void clear_terminal() { printf("\x1b[2J\x1b[H"); }
