#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_apple(Coordinate* appleCoords, Coordinate* snakeCoords,
                 int snakeLength, int startMessageVisible) {
  // if no apple then get new location and print it
  // move_snake() sets appleCoords.x to -1 when it gets an apple
  if (appleCoords->x == -1) {
    int validPosition = 0;
    while (!validPosition) {
      validPosition = 1;

      // get random coordinates
      appleCoords->x = (rand() % COLS) * 2 + 2;
      appleCoords->y = (rand() % ROWS) + 5;

      // makes sure it's not a location where the snake is
      for (int i = 0; i < snakeLength; i++) {
        if (appleCoords->x == snakeCoords[i].x &&
            appleCoords->y == snakeCoords[i].y) {
          validPosition = 0;
          break;
        }
      }

      // makes sure the first apple isn't where the start message is
      // doesn't do it if start message not visible or already invalid
      if (startMessageVisible && validPosition) {
        // index of P (10) in startMessage and index of t (34) in startMessage
        if (appleCoords->x >= 10 && appleCoords->x <= 34 &&
            appleCoords->y == ROWS / 2 + 2) {
          validPosition = 0;
        }
      }
    }

    // print new apple
    printf("\e[H");
    printf("\e[%iB\e[%iC🍎", appleCoords->y, appleCoords->x);
    fflush(stdout);
  }
}