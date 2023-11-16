#include "utils.h"
#include <stdio.h>

void change_and_print(int* snakeLength, Coordinate* snakeCoords, int appleX);
void print(int i, Coordinate* snakeCoords);

void move_snake(int xDir, int yDir, int* snakeLength, int* gameOver,
                Coordinate* snakeCoords, Coordinate* appleCoords, int* score) {
  if (snakeCoords[0].x == appleCoords->x &&
      snakeCoords[0].y == appleCoords->y) {
    appleCoords->x = -1;
    *snakeLength = *snakeLength + 1;
  }
  change_and_print(snakeLength, snakeCoords, appleCoords->x);
  if (xDir == 1) {
    // right
    snakeCoords[0].x++;
    if (snakeCoords[0].x > COLS) {
      *gameOver = 1;
      *snakeLength = 1;
      *score = -1;
    }
  } else if (xDir == -1) {
    // left
    snakeCoords[0].x--;
    if (snakeCoords[0].x < 0) {
      *gameOver = 1;
      *snakeLength = 1;
      *score = -1;
    }
  } else if (yDir == 1) {
    // down
    snakeCoords[0].y++;
    if (snakeCoords[0].y > ROWS) {
      *gameOver = 1;
      *snakeLength = 1;
      *score = -1;
    }
  } else if (yDir == -1) {
    // up
    snakeCoords[0].y--;
    if (snakeCoords[0].y < 0) {
      *gameOver = 1;
      *snakeLength = 1;
      *score = -1;
    }
  }
  print(0, snakeCoords);
}

void change_and_print(int* snakeLength, Coordinate* snakeCoords, int appleX) {
  if (appleX != -1) {
    printf("\e[%iB\e[%iC·", snakeCoords[*snakeLength - 1].y,
           snakeCoords[*snakeLength - 1].x);
    printf("\e[%iF", snakeCoords[*snakeLength - 1].y);
    fflush(stdout);
  }
  for (int i = *snakeLength - 1; i > 0; i--) {
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