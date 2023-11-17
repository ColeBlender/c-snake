#include "utils.h"
#include <stdio.h>

void change_and_print(int* snakeLength, Coordinate* snakeCoords, int appleX);
void print(int i, Coordinate* snakeCoords);

void move_snake(int xDir, int yDir, int* snakeLength, int* gameOver,
                Coordinate* snakeCoords, Coordinate* appleCoords) {
  if (snakeCoords[0].x == appleCoords->x &&
      snakeCoords[0].y == appleCoords->y) {
    appleCoords->x = -1;
    *snakeLength = *snakeLength + 1;
  }
  change_and_print(snakeLength, snakeCoords, appleCoords->x);
  if (xDir == 1) {
    // right
    if (++snakeCoords[0].x > COLS) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (xDir == -1) {
    // left
    if (--snakeCoords[0].x < 0) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (yDir == 1) {
    // down
    if (++snakeCoords[0].y > ROWS + 3) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (yDir == -1) {
    // up
    if (--snakeCoords[0].y < 4) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  }
  for (int i = 1; i < *snakeLength; i++) {
    if (snakeCoords[0].x == snakeCoords[i].x &&
        snakeCoords[0].y == snakeCoords[i].y) {
      *gameOver = 1;
      *snakeLength = 1;
      break;
    }
  }
  print(0, snakeCoords);
}

void change_and_print(int* snakeLength, Coordinate* snakeCoords, int appleX) {
  if (appleX != -1) {
    printf("\e[H");
    printf("\e[%iB\e[%iC·", snakeCoords[*snakeLength - 1].y,
           snakeCoords[*snakeLength - 1].x);
    printf("\e[H");
    fflush(stdout);
  }
  for (int i = *snakeLength - 1; i > 0; i--) {
    snakeCoords[i].x = snakeCoords[i - 1].x;
    snakeCoords[i].y = snakeCoords[i - 1].y;
    print(i, snakeCoords);
  }
}

void print(int i, Coordinate* snakeCoords) {
  printf("\e[H");
  printf("\e[%iB\e[%iC▓", snakeCoords[i].y, snakeCoords[i].x);
  printf("\e[H");
  fflush(stdout);
}