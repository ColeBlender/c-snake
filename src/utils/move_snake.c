#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static void print_tail(int* snakeLength, Coordinate* snakeCoords, int appleX);
static void print_snake_piece(int i, Coordinate* snakeCoords);

//
//
//
void move_snake(int xDir, int yDir, int* snakeLength, int* gameOver,
                Coordinate* snakeCoords, Coordinate* appleCoords) {
  // check if got apple
  if (snakeCoords[0].x == appleCoords->x &&
      snakeCoords[0].y == appleCoords->y) {
    appleCoords->x = -1;
  }
  print_tail(snakeLength, snakeCoords, appleCoords->x);
  if (xDir == 1) {
    // right
    snakeCoords[0].x += 2;
    if (snakeCoords[0].x > COLS * 2) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (xDir == -1) {
    // left
    snakeCoords[0].x -= 2;
    if (snakeCoords[0].x <= 0) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (yDir == 1) {
    // down
    if (++snakeCoords[0].y > ROWS + 4) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  } else if (yDir == -1) {
    // up
    if (--snakeCoords[0].y < 5) {
      *gameOver = 1;
      *snakeLength = 1;
    }
  }
  if (!*gameOver) {
    // check if run into self
    for (int i = 1; i < *snakeLength; i++) {
      if (snakeCoords[0].x == snakeCoords[i].x &&
          snakeCoords[0].y == snakeCoords[i].y) {
        *gameOver = 1;
        *snakeLength = 1;
        break;
      }
    }
  }
  // print head
  print_snake_piece(0, snakeCoords);
}

//
//
//
static void print_tail(int* snakeLength, Coordinate* snakeCoords, int appleX) {
  if (appleX == -1) {
    // just got apple so increase snakeLength
    *snakeLength = *snakeLength + 1;
  } else {
    // didn't just get apple so replace last part of tail with black
    printf("\e[H\e[%iB\e[%iC⬛️", snakeCoords[*snakeLength - 1].y,
           snakeCoords[*snakeLength - 1].x);
    fflush(stdout);
  }
  // print tail everywhere where the previous snake was
  for (int i = *snakeLength - 1; i > 0; i--) {
    snakeCoords[i].x = snakeCoords[i - 1].x;
    snakeCoords[i].y = snakeCoords[i - 1].y;
    print_snake_piece(i, snakeCoords);
  }
}

//
//
//
static void print_snake_piece(int i, Coordinate* snakeCoords) {
  // if runs into left wall it fucks up so need this
  int snakeX = snakeCoords[i].x == 0 ? -2 : snakeCoords[i].x;
  printf("\e[H\e[%iB\e[%iC🟩", snakeCoords[i].y, snakeX);
  fflush(stdout);
}