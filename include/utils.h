#ifndef _UTILS_H
#define _UTILS_H

#ifndef _TABLE_H
#include "./game/table.h"
#endif

// logic utils
int yes_or_no_input();
int is_num(char *, unsigned);

// char* (string) manipulation
int is_alpha_str(char *);
void str_to_lower(char *);
char *strip(char *, unsigned);
char *p_input(char *, char *, unsigned);
void simple_table_print(Table *);

#endif
