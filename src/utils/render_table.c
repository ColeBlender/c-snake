#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_table() {
  FILE* file;
  char firstLine[100];
  file = fopen("high-scores.txt", "r");
  if (!file) {
    perror("Error opening file");
  }
  fgets(firstLine, sizeof(firstLine), file);
  fclose(file);

  char* highScore = strchr(firstLine, ' ');
  highScore++;

  // high score
  printf("\e[H");
  printf("\e[%iB\e[%iC High Score: %s ", 0,
         COLS / 2 - (14 + (int)strlen(highScore)) / 2, highScore);
  printf(" \n");
  printf("\e[F");
  // score board
  printf("\e[%iB\e[%iC Score: 0 ", 1, COLS / 2 - 4);
  printf(" \n\n");
  printf("\e[F");
  // top row
  printf("┌");
  for (int i = 0; i < COLS; i++) {
    printf("─");
  }
  printf("┐\n");

  // middle rows
  for (int j = 0; j < ROWS; j++) {
    printf("│");
    for (int i = 0; i < COLS; i++) {
      printf("·");
    }
    printf("│\n");
  }

  // bottom row
  printf("└");
  for (int i = 0; i < COLS; i++) {
    printf("─");
  }
  printf("┘\n");

  // move cursor back to top
  printf("\e[%iA", ROWS + 2);
}