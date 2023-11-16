#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void check_score(int* score, int appleX) {
  if (appleX < 0) {
    *score = *score + 1;
    printf("\e[%iB\e[%iCScore: %d", 0, COLS / 2 - 3, *score);
    printf("\e[%iF", 0);
    fflush(stdout);
  }
}