#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main() {
  struct termios oldT;
  init_terminal(&oldT, 1);

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
    int score = 0;
    int xDir = 0, yDir = 0;
    int startMessageGone = 0;
    Coordinate appleCoords = {-1, -1};
    snakeCoords[0].x = COLS + 1;
    snakeCoords[0].y = ROWS / 2 + 5;

    char startMessage[] = " Press any arrow to start ";
    printf("\e[H");
    printf("\e[%iB\e[%iC%s", ROWS / 2 + 2,
           COLS + 2 - (int)strlen(startMessage) / 2, startMessage);

    // this is the game loop
    // breaks out if user quits or loses
    while (!quit && !gameOver) {
      int gameStarted = xDir != 0 || yDir != 0;
      if (gameStarted && !startMessageGone) {
        printf("\e[H");
        printf("\e[%iB\e[%iC⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️", ROWS / 2 + 2,
               COLS + 2 - (int)strlen(startMessage) / 2);
        startMessageGone = 1;
      }

      draw_apple(&appleCoords, snakeCoords, snakeLength, startMessageGone);

      move_snake(xDir, yDir, &snakeLength, &gameOver, snakeCoords,
                 &appleCoords);

      check_score(&score, appleCoords.x);

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