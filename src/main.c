#ifndef __INCLUDE__H_
#include "./_include_.h"
#endif

int main(int arc, char *argv[]) {

  char red[] = "\033[1;32m";
  char none[] = "\033[0m";

  printf("\n%sAyooo%s, World!\n", red, none);

  return 0;
}
