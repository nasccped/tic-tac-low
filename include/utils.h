#ifndef _UTILS_H
#define _UTILS_H

// logic utils
int yes_or_no_input();
int is_num(char *, unsigned);

// char* (string) manipulation
int is_alpha_str(char *);
void str_to_lower(char *);
char *strip(char *, unsigned);
char *input(char *, char *, unsigned);

#endif
