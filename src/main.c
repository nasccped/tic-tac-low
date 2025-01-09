#include "./headers/__INCLUDE__.H"
#include "./headers/const_vars.h"
#include "./headers/visuals.h"

int main(int argc, char *argv[]) {

  const char *COLORS[] = {
      BOLD_RED_NONE,
      BOLD_GREEN_NONE,
      BOLD_YELLOW_NONE,
  };

  clear_terminal();

  char *hlwd = "  Hello, World!";
  size_t len = strlen(hlwd);

  printf("\n  ");
  for (int i = 0; i < len; i++) {
    printf("%s%c", COLORS[i % 3], hlwd[i]);
  }
  printf("%s\n", RESET_ESCAPE);

  return 0;
}
