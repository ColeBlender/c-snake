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

  // when game gets turned on
  // breaks out when user quits
  while (!quit) {
    // init game board
    render_table();

    // init game variables
    int gameOver = 0;
    int xDir = 1;
    int yDir = 0;
    Coordinate appleCoords = {-1, -1};
    snakeCoords[0].x = COLS / 2;
    snakeCoords[0].y = ROWS / 2;

    // this is the game loop
    // breaks out if user quits or loses
    while (!quit && !gameOver) {
      draw_apple(&appleCoords, snakeCoords, snakeLength);

      move_snake(xDir, yDir, &snakeLength, &gameOver, snakeCoords,
                 &appleCoords);

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