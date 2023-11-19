#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void terminal_to_game_mode(struct termios* oldT, int start) {
  printf("\e[?25l"); // hide the cursor

  // only do this when game is first started
  if (start) {
    printf("\e[2J"); // clear the screen
    srand(time(NULL)); // set random seed
  }

  // switch terminal to non-canonical mode, disable echo
  tcgetattr(STDIN_FILENO, oldT);
  struct termios newT = *oldT;
  newT.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newT);
}