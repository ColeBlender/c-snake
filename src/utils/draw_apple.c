#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void draw_apple(Coordinate* appleCoords) {
  if (appleCoords->x < 0) {
    appleCoords->x = rand() % COLS;
    appleCoords->y = rand() % ROWS;

    printf("\e[%iB\e[%iC❤︎", appleCoords->y, appleCoords->x);
    printf("\e[%iF", appleCoords->y);
    fflush(stdout);
  }
}