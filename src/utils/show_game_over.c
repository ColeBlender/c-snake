#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void show_game_over(int* quit) {
  char gMessage[] = " GAME OVER! ";
  char rMessage[] = " Press R to play again! ";
  char qMessage[] = " Press Q to quit! ";

  printf("\e[H");
  printf("\e[%iB\e[%iC%s", ROWS / 2, COLS / 2 - (int)strlen(gMessage) / 2 + 1,
         gMessage);
  printf("\e[%iB\e[%iD%s", 2,
         (int)(strlen(gMessage) + (strlen(rMessage) - strlen(gMessage)) / 2),
         rMessage);
  printf("\e[%iB\e[%iD%s", 2,
         (int)(strlen(rMessage) + (strlen(qMessage) - strlen(rMessage)) / 2),
         qMessage);
  printf("\e[H");
  fflush(stdout);

  int ch;
  do {
    ch = getchar();
    if (ch == 'r' || ch == 'R') {
      break;
    } else if (ch == 'q' || ch == 'Q') {
      *quit = 1;
      break;
    }
  } while (1); // infinite loop, exits only on 'r' or 'q'
}