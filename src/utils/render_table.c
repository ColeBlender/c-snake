#include "utils.h"
#include <stdio.h>

void render_table() {
  // top row
  printf("┌");
  for (int i = 0; i < COLS; i++) {
    printf("─");
  }
  printf("┐\n");

  // middle rows
  for (int j = 0; j < ROWS; j++) {
    printf("│");
    for (int i = 0; i < COLS; i++) {
      printf("·");
    }
    printf("│\n");
  }

  // bottom row
  printf("└");
  for (int i = 0; i < COLS; i++) {
    printf("─");
  }
  printf("┘\n");

  // move cursor back to top
  printf("\e[%iA", ROWS + 2);
}