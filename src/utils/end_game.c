#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void end_game(struct termios* oldT) {
  // move cursor to top of screen and reshow cursor
  printf("\e[H\e[?25h");

  // reset terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, oldT);
}