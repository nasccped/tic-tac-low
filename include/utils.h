#ifndef _UTILS_H
#define _UTILS_H

#ifndef _TABLE_H
#include "./game/table.h"
#endif

// logic utils
int yes_or_no_input();
int is_num(char *, unsigned);
int is_alpha_str(char *);
int chose_random_uns(unsigned [], unsigned);
unsigned find_on_arr(unsigned [], unsigned, unsigned);
unsigned convert_row_col_intouns(unsigned, unsigned);
void p_sleep(unsigned);

// char* (string) manipulation
void str_to_lower(char *);
char *strip(char *, unsigned);
char *p_input(char *, char *, unsigned);

// visuals
void simple_table_print(Table *);

#endif
