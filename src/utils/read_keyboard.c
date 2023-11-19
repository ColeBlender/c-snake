#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void read_keyboard(int* xDir, int* yDir) {
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

  if (FD_ISSET(STDIN_FILENO, &fds)) {
    int ch = getchar();
    if (ch == 27) { // first character of the escape sequence
      getchar(); // skip '['
      ch = getchar(); // read the direction character
      switch (ch) {
      case 'A': // up arrow
        if (*yDir != 1) {
          *xDir = 0;
          *yDir = -1;
        }
        break;
      case 'B': // down arrow
        if (*yDir != -1) {
          *xDir = 0;
          *yDir = 1;
        }
        break;
      case 'C': // right arrow
        if (*xDir != -1) {
          *xDir = 1;
          *yDir = 0;
        }
        break;
      case 'D': // left arrow
        if (*xDir != 1) {
          *xDir = -1;
          *yDir = 0;
        }
        break;
      }
    }
  }
}