#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_SCORES 10
#define MAX_NAME_LENGTH 4

typedef struct {
  int score;
  char name[MAX_NAME_LENGTH + 1]; // +1 for null terminator
} ScoreEntry;

static int file_func(int* score, struct termios* oldT);

//
//
//
void show_game_over(int* quit, int* score, struct termios* oldT) {
  char gMessage[] = " GAME OVER! ";
  char rMessage[] = " Press R to play again! ";
  char qMessage[] = " Press Q to quit! ";

  // print gMessage
  printf("\e[H");
  printf("\e[%iB\e[%iC%s", ROWS / 2 + 3, COLS - (int)strlen(gMessage) / 2 + 2,
         gMessage);
  fflush(stdout);

  // see if top 10 score and prompt user to type name
  file_func(score, oldT);

  // print rMessage and qMessage
  printf("\e[H");
  printf("\e[%iB\e[%iC%s", ROWS / 2 + 5, COLS - (int)strlen(rMessage) / 2 + 2,
         rMessage);
  printf("\e[%iB\e[%iD%s", 2,
         (int)(strlen(rMessage) + (strlen(qMessage) - strlen(rMessage)) / 2),
         qMessage);
  fflush(stdout);

  int ch;
  do {
    ch = getchar();
    if (ch == 'r' || ch == 'R') {
      *score = -1;
      break;
    } else if (ch == 'q' || ch == 'Q') {
      *score = -1;
      *quit = 1;
      break;
    }
  } while (1); // infinite loop, exits only on 'r' or 'q'
}

//
//
//
static int file_func(int* score, struct termios* oldT) {
  FILE* file;
  char line[100];
  ScoreEntry scores[MAX_SCORES];
  int scoreCount = 0;

  file = fopen("high-scores.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(line, sizeof(line), file) && scoreCount < MAX_SCORES) {
    ScoreEntry entry;
    if (sscanf(line, "%*d. %d (%4s)", &entry.score, entry.name) == 2) {
      scores[scoreCount++] = entry;
    }
  }
  fclose(file);

  char newName[MAX_NAME_LENGTH + 1];

  // Check if the new score is a top score
  int position = -1;
  for (int i = 0; i < scoreCount; i++) {
    if (*score > scores[i].score) {
      position = i;
      break;
    }
  }

  if (position != -1 || scoreCount < MAX_SCORES) {
    char highScoreMessage[] = " Great Score! Enter Name: ";

    // print highScoreMessage
    printf("\e[H");
    printf("\e[%iB\e[%iC%s", ROWS / 2 + 5,
           COLS - (int)strlen(highScoreMessage) / 2 + 2, highScoreMessage);
    fflush(stdout);

    // tcsetattr(STDIN_FILENO, TCSANOW, oldT);
    // printf("\e[?25h"); // show the cursor

    // printf("\e[?25l"); // hide the cursor

    // switch terminal to non-canonical mode, disable echo
    // tcgetattr(STDIN_FILENO, oldT);
    // struct termios newT = *oldT;
    // newT.c_lflag &= ~(ICANON | ECHO);
    // tcsetattr(STDIN_FILENO, TCSANOW, &newT);

    if (scanf("%4s", newName) != 1) {
      perror("Error reading name");
      return 1;
    }

    newName[MAX_NAME_LENGTH] = '\0';

    for (int i = 0; newName[i] != '\0'; i++) {
      newName[i] = toupper(newName[i]);
    }

    // Insert new score
    if (position == -1) {
      position = scoreCount;
    }

    for (int i = MAX_SCORES - 1; i >= position; i--) {
      scores[i] = scores[i - 1];
    }
    scores[position].score = *score;
    strncpy(scores[position].name, newName, MAX_NAME_LENGTH);

    // Write updated scores back to file
    file = fopen("high-scores.txt", "w");
    if (!file) {
      perror("Error opening file for writing");
      return 1;
    }

    if (scoreCount < MAX_SCORES) {
      scoreCount++;
    }

    for (int i = 0; i < scoreCount; i++) {
      fprintf(file, "%d. %d (%s)\n", i + 1, scores[i].score, scores[i].name);
    }

    fclose(file);

    printf("\e[H");
    printf("\e[%iB\e[%iC⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️", ROWS / 2 + 5,
           COLS - (int)strlen(highScoreMessage) / 2 + 1);
    fflush(stdout);
  }

  return 0;
}