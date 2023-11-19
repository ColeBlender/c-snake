#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void check_score(int* score, int appleX) {
  if (appleX < 0) {
    *score = *score + 1;
    printf("\e[H");
    printf("\e[%iB\e[%iC Score: %d ", 2, COLS - 3, *score);
    fflush(stdout);
  }
}