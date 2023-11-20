#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_board() {
  // get firstLine from high-scores.txt
  FILE* file;
  char firstLine[100];
  file = fopen("high-scores.txt", "r");
  if (!file) {
    perror("Error opening file");
  }
  fgets(firstLine, sizeof(firstLine), file);
  fclose(file);

  // set highScore
  char* highScore = "0";
  char* highScoreSafe = strchr(firstLine, ' ');
  if (highScoreSafe) {
    highScore = ++highScoreSafe;
  }

  // remove \n if it's at the end of highScore
  size_t len = strlen(highScore);
  if (len > 0 && highScore[len - 1] == '\n') {
    highScore[len - 1] = '\0';
  }

  // clear high score from last game
  printf("\e[H\e[%iB\e[%iC                                   ", 0, 0);
  // print high score
  if (strlen(highScore) > 1) {
    printf("\e[H\e[%iB\e[%iCHigh Score: %s", 0, COLS - 8, highScore);
  }

  // print score board
  printf("\e[F\e[%iB\e[%iCScore: 0\n\n\n", 1, COLS - 2);

  // print board
  printf("\e[F");
  for (int i = 0; i < ROWS + 2; i++) {
    // left border
    printf("⬜️");
    for (int j = 0; j < COLS; j++) {
      // if top or bottom border print white otherwise print black
      if (i == 0 || i == ROWS + 1) {
        printf("⬜️");
      } else {
        printf("⬛️");
      }
    }
    // right border
    printf("⬜️\n");
  }
}