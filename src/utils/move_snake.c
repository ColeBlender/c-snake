#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void change_and_print(int snakeLength, Coordinate* snakeCoords);
void print(int i, Coordinate* snakeCoords);

void move_snake(int xDir, int yDir, int snakeLength, int* gameOver,
                Coordinate* snakeCoords) {
  change_and_print(snakeLength, snakeCoords);
  if (xDir == 1) {
    snakeCoords[0].x++;
    if (snakeCoords[0].x > COLS) {
      *gameOver = 1;
    }
  } else if (xDir == -1) {
    snakeCoords[0].x--;
    if (snakeCoords[0].x < 0) {
      *gameOver = 1;
    }
  } else if (yDir == 1) {
    snakeCoords[0].y++;
    if (snakeCoords[0].y > ROWS) {
      *gameOver = 1;
    }
  } else if (yDir == -1) {
    snakeCoords[0].y--;
    if (snakeCoords[0].y < 0) {
      *gameOver = 1;
    }
  }
  print(0, snakeCoords);
  // printf("\e[%iB\e[%iC·", snakeCoords[snakeLength].y,
  //        snakeCoords[snakeLength].x);
  // printf("\e[%iF", snakeCoords[snakeLength].y);
  // fflush(stdout);
}

void change_and_print(int snakeLength, Coordinate* snakeCoords) {
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeCoords[i].x = snakeCoords[i - 1].x;
    snakeCoords[i].y = snakeCoords[i - 1].y;
    print(i, snakeCoords);
  }
}

void print(int i, Coordinate* snakeCoords) {
  printf("\e[%iB\e[%iC▓", snakeCoords[i].y, snakeCoords[i].x);
  printf("\e[%iF", snakeCoords[i].y);
  fflush(stdout);
}