#ifndef _OPTIONS_H
#define _OPTIONS_H

#define OPTION_END "![OPTION END]"

static const char *MENU_OPTIONS[] = {
  "Play", "About", "Quit", OPTION_END
};

void print_options(unsigned, const char **);

#endif
