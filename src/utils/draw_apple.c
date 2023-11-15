#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void draw_apple(Coordinate* appleCoords, Coordinate* snakeCoords,
                int snakeLength) {
  if (appleCoords->x < 0) {
    int cleared;
    do {
      appleCoords->x = rand() % COLS;
      appleCoords->y = rand() % ROWS;

      cleared = 1;
      for (int i = 0; i < snakeLength; i++) {
        if (appleCoords->x == snakeCoords[i].x &&
            appleCoords->y == snakeCoords[i].y) {
          cleared = 0;
          break;
        }
      }
    } while (!cleared);
    printf("\e[%iB\e[%iC❤︎", appleCoords->y, appleCoords->x);
    printf("\e[%iF", appleCoords->y);
    fflush(stdout);
  }
}