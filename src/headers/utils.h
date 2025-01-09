#ifndef _UTILS_H_
#define _UTILS_H_

// logic utils
int yes_or_no_input();

// char* (string) manipulation
int is_alpha_str(char *from);
void str_to_lower(char *dest);
char *strip(char *from, unsigned m_len);

#endif
