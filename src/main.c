#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
  struct termios oldT;
  init_terminal(&oldT);

  int quit = 0;
  int snakeLength = 1;
  Coordinate snakeCoords[COLS * ROWS];

  // when game gets turned on
  // breaks out when user quits
  while (!quit) {
    // init game board
    render_table();

    // init game variables
    int gameOver = 0;
    int score = -1;
    int xDir = 1, yDir = 0;
    Coordinate appleCoords = {-1, -1};
    snakeCoords[0].x = COLS;
    snakeCoords[0].y = ROWS / 2;

    // this is the game loop
    // breaks out if user quits or loses
    while (!quit && !gameOver) {
      check_score(&score, appleCoords.x);

      draw_apple(&appleCoords, snakeCoords, snakeLength);

      move_snake(xDir, yDir, &snakeLength, &gameOver, snakeCoords,
                 &appleCoords);

      // adjust sleep time logarithmically based on score
      // add 2 to score because score becomes -1 on loss
      int sleepTime = calc_sleep_time(score);
      usleep(sleepTime);
      read_keyboard(&xDir, &yDir);
    }

    // the game is now done
    // only triggers if the game was lost
    if (!quit) {
      show_game_over(&quit, &score, &oldT);
    }
  }

  end_game(&oldT);

  return 0;
}