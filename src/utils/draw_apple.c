#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void draw_apple(Coordinate* appleCoords, Coordinate* snakeCoords,
                int snakeLength, int startMessageGone) {
  if (appleCoords->x < 0) {
    int cleared;
    do {
      appleCoords->x = (rand() % COLS) * 2 + 2;
      appleCoords->y = (rand() % ROWS) + 5;

      cleared = 1;
      for (int i = 0; i < snakeLength; i++) {
        if (appleCoords->x == snakeCoords[i].x &&
            appleCoords->y == snakeCoords[i].y) {
          cleared = 0;
          break;
        }
      }
      if (!startMessageGone) {
        // index of P in startMessage and index of t in startMessage
        if (appleCoords->x >= 10 && appleCoords->x <= 34 &&
            appleCoords->y == ROWS / 2 + 2) {
          cleared = 0;
        }
      }
    } while (!cleared);
    printf("\e[H");
    printf("\e[%iB\e[%iC🍎", appleCoords->y, appleCoords->x);
    fflush(stdout);
  }
}