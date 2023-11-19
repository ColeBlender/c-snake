#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void end_game(struct termios* oldT) {
  printf("\e[H"); // move cursor to top of screen
  printf("\e[?25h"); // reshow cursor

  // reset terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, oldT);
}