#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void end_game(Coordinate* snakeCoords, struct termios* oldT) {
  // reshow cursor
  printf("\e[?25h");

  // reset terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, oldT);

  // free memory
  free(snakeCoords);
}