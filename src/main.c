#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
  struct termios oldT;
  init_terminal(&oldT);

  int quit = 0;
  int snakeLength = 1;
  int capacity = 1000;

  Coordinate* snakeCoords = malloc(capacity * sizeof(Coordinate));
  if (!snakeCoords) {
    perror("Memory allocation failed");
    return 1;
  }

  for (int i = 0; i < capacity; i++) {
    snakeCoords[i].x = -1;
    snakeCoords[i].y = -1;
  }

  // when game gets turned on
  // breaks out when user quits
  while (!quit) {
    // init game board
    render_table();

    // init game variables
    int gameOver = 0;
    int xDir = 1;
    int yDir = 0;
    Coordinate appleCoords;
    appleCoords.x = -1;
    appleCoords.y = -1;
    snakeCoords[0].x = COLS / 2;
    snakeCoords[0].y = ROWS / 2;

    // this is the game loop
    // breaks out if user quits or loses
    while (!quit && !gameOver) {
      if (appleCoords.x < 0) {
        appleCoords.x = rand() % COLS;
        appleCoords.y = rand() % ROWS;

        printf("\e[%iB\e[%iC🍎", appleCoords.y, appleCoords.x);
        printf("\e[%iF", appleCoords.y);
      }

      if (snakeCoords[0].x == appleCoords.x &&
          snakeCoords[0].y == appleCoords.y) {
        appleCoords.x = -1;
        if (++snakeLength == capacity) {
          capacity *= 2;
          Coordinate* temp =
              realloc(snakeCoords, capacity * sizeof(Coordinate));
          if (!temp) {
            perror("Memory reallocation failed");
            return 1;
          }
          snakeCoords = temp;
        }
      }

      // replace last spot
      printf("\e[%iB\e[%iC·", snakeCoords[snakeLength - 1].y,
             snakeCoords[snakeLength - 1].x);
      printf("\e[%iF", snakeCoords[snakeLength - 1].y);

      for (int i = 0; i < snakeLength; i++) {
        // draw snake
        printf("\e[%iB\e[%iC▓", snakeCoords[i].y, snakeCoords[i].x);
        printf("\e[%iF", snakeCoords[i].y);
        fflush(stdout);
      }

      if (xDir == 1) {
        for (int i = snakeLength - 1; i > 1; i--) {
          snakeCoords[i].x = snakeCoords[i - 1].x;
        }
        if (++snakeCoords[0].x > COLS) {
          gameOver = 1;
        }
      } else if (xDir == -1) {
        for (int i = snakeLength - 1; i > 1; i--) {
          snakeCoords[i].x = snakeCoords[i - 1].x;
        }
        if (--snakeCoords[0].x < 0) {
          gameOver = 1;
        }
      } else if (yDir == 1) {
        for (int i = snakeLength - 1; i > 1; i--) {
          snakeCoords[i].y = snakeCoords[i - 1].y;
        }
        if (++snakeCoords[0].y > ROWS) {
          gameOver = 1;
        }
      } else if (yDir == -1) {
        for (int i = snakeLength - 1; i > 1; i--) {
          snakeCoords[i].y = snakeCoords[i - 1].y;
        }
        if (--snakeCoords[0].y < 0) {
          gameOver = 1;
        }
      }

      usleep(SLEEP_TIME);
      read_keyboard(&xDir, &yDir, &quit);
    }

    // the game is now done
    // only triggers if the game was lost
    if (!quit) {
      show_game_over();
    }
  }

  end_game(snakeCoords, &oldT);

  return 0;
}