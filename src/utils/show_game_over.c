#include "utils.h"
#include <stdio.h>

void show_game_over() {
  printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
  printf("\e[%iF", ROWS / 2);
  fflush(stdout);
  getchar();
}