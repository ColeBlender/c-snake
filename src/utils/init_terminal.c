#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void init_terminal(struct termios* oldT) {
  // hide cursor
  printf("\e[?25l");

  // set random seed
  srand(time(NULL));

  // switch terminal to non-canonical mode, disable echo
  tcgetattr(STDIN_FILENO, oldT);
  struct termios newT = *oldT;
  newT.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newT);
}