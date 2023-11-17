#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void end_game(struct termios* oldT) {
  // reshow cursor
  printf("\e[H");
  printf("\e[?25h");

  // reset terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, oldT);
}