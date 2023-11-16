#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void read_keyboard(int* xDir, int* yDir) {
  // read keyboard
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
  if (FD_ISSET(STDIN_FILENO, &fds)) {
    int ch = getchar();
    if (ch == 27) { // First character of the escape sequence
      getchar(); // Skip '['
      ch = getchar(); // Read the direction character
      switch (ch) {
      case 'A': // Up arrow
        if (*yDir != 1) {
          *xDir = 0;
          *yDir = -1;
        }
        break;
      case 'B': // Down arrow
        if (*yDir != -1) {
          *xDir = 0;
          *yDir = 1;
        }
        break;
      case 'C': // Right arrow
        if (*xDir != -1) {
          *xDir = 1;
          *yDir = 0;
        }
        break;
      case 'D': // Left arrow
        if (*xDir != 1) {
          *xDir = -1;
          *yDir = 0;
        }
        break;
      }
    }
  }
}