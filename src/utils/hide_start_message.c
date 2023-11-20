#include "utils.h"
#include <stdio.h>
#include <string.h>

void hide_start_message(int xDir, int yDir, int* startMessageVisible,
                        char startMessage[]) {
  int firstMoveMade = xDir != 0 || yDir != 0;
  // if player has made first move and the message is still visible
  if (firstMoveMade && *startMessageVisible) {
    // hide start message
    printf("\e[H\e[%iB\e[%iC⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️", ROWS / 2 + 2,
           COLS + 2 - (int)strlen(startMessage) / 2);
    *startMessageVisible = 0;
  }
}