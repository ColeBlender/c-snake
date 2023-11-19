#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_board() {
  FILE* file;
  char firstLine[100];
  file = fopen("high-scores.txt", "r");
  if (!file) {
    perror("Error opening file");
  }
  fgets(firstLine, sizeof(firstLine), file);
  fclose(file);

  char* highScore = "0";
  char* test = strchr(firstLine, ' ');
  if (test) {
    highScore = test;
    highScore++;
  }
  // Remove \n if it's at the end of highScore
  size_t len = strlen(highScore);
  if (len > 0 && highScore[len - 1] == '\n') {
    highScore[len - 1] = '\0';
  }

  // high score
  printf("\e[H");
  printf("\e[%iB\e[%iC                                   ", 0, 0);
  printf("\e[H");
  printf("\e[%iB\e[%iCHigh Score: %s", 0, COLS - 8, highScore);
  printf(" \n");
  printf("\e[F");

  // score board
  printf("\e[%iB\e[%iCScore: 0", 1, COLS - 2);
  printf(" \n\n\n");
  printf("\e[F");

  // top row
  printf("⬜️");
  for (int i = 0; i < COLS; i++) {
    printf("⬜️");
  }
  printf("⬜️\n");

  // middle rows
  for (int j = 0; j < ROWS; j++) {
    printf("⬜️");
    for (int i = 0; i < COLS; i++) {
      printf("⬛️");
    }
    printf("⬜️\n");
  }

  // bottom row
  printf("⬜️");
  for (int i = 0; i < COLS; i++) {
    printf("⬜️");
  }
  printf("⬜️\n");

  // move cursor back to top
  printf("\e[%iA", ROWS + 2);
}