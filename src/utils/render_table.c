#include "utils.h"
#include <stdio.h>

void render_table() {
  // score board
  // printf(" ");
  // int scoreTextLength = 9; // Length of "Score: 0"
  // int leftPadding =
  //     (COLS - scoreTextLength) / 2; // Calculate left padding for centering
  // for (int i = 0; i < leftPadding; i++) {
  //   printf(" ");
  // }
  // printf("Score: 0"); // Print the score text
  // for (int i = 0; i < COLS - leftPadding - scoreTextLength; i++) {
  //   printf(" ");
  // }
  // printf(" \n");
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