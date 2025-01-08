#ifndef _COLORS_H_
#define _COLORS_H_

#ifndef __INCLUDE__H_
#include "../_include_.h"
#endif

static const char ESCAPE_RESET  = "\033[0m"   ;
static const char BOLD_RED[]    = "\033[1;31m";
static const char BOLD_GREEN[]  = "\033[1;32m";
static const char BOLD_YELLOW[] = "\033[1;33m";

extern bool COLORED_PRINT;

#endif
