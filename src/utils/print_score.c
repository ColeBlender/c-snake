#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_score(int* score, int appleX) {
  // if apple just consumed then increment score by 1
  if (appleX < 0) {
    *score = *score + 1;

    // print new score at top
    printf("\e[H\e[%iB\e[%iC Score: %d ", 2, COLS - 3, *score);
    fflush(stdout);
  }
}