#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

int main() {
  struct termios oldT;
  terminal_to_game_mode(&oldT, 1);

  int quit = 0;
  int snakeLength = 1;
  Coordinate snakeCoords[COLS * ROWS];

  // when game gets turned on
  // breaks out when user quits
  while (!quit) {
    print_board();

    // init game variables
    int gameOver = 0;
    int score = 0;
    int xDir = 0, yDir = 0;
    int startMessageVisible = 1;
    Coordinate appleCoords = {-1, -1};
    snakeCoords[0].x = COLS + 1;
    snakeCoords[0].y = ROWS / 2 + 5;

    // print startMessage
    char startMessage[] = " Press any arrow to start ";
    printf("\e[H\e[%iB\e[%iC%s", ROWS / 2 + 2,
           COLS + 2 - (int)strlen(startMessage) / 2, startMessage);

    // this is the game loop
    // breaks out if user loses
    while (!gameOver) {
      hide_start_message(xDir, yDir, &startMessageVisible, startMessage);
      print_apple(&appleCoords, snakeCoords, snakeLength, startMessageVisible);
      move_snake(xDir, yDir, &snakeLength, &gameOver, snakeCoords,
                 &appleCoords);
      print_score(&score, appleCoords.x);
      sleep_time(score);
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