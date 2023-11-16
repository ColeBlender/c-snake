#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void init_terminal(struct termios* oldT) {
  printf("\e[?25l"); // hide the cursor
  printf("\e[2J"); // clear the screen
  printf("\e[H"); // move cursor to top left corner

  // set random seed
  srand(time(NULL));

  // switch terminal to non-canonical mode, disable echo
  tcgetattr(STDIN_FILENO, oldT);
  struct termios newT = *oldT;
  newT.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newT);
}