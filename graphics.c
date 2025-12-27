#include "graphics.h"
#include <stdio.h>

struct termios orig_termios;

void clear() { printf("\e[1;1H\e[2J"); }

void DrawBorder(App *a) {
  // Print the title centered above the box
  int titleLength = 0;
  for (titleLength = 0; a->title[titleLength] != '\0'; titleLength++)
    ;

  int padding = (a->maxWidth - titleLength) / 2;

  // Print empty spaces before the title
  for (int i = 0; i < padding; i++) {
    printf(" ");
  }

  printf("%s\n", a->title);

  // Print the top border with corners
  printf("╔");
  for (int i = 0; i < a->maxWidth - 2; i++) {
    printf("═");
  }
  printf("╗\n");

  // Print the sides of the box
  for (int i = 0; i < a->maxHeight - 2; i++) {
    printf("║");
    for (int j = 0; j < a->maxWidth - 2; j++) {
      printf(" "); // Empty space inside the box
    }
    printf("║\n");
  }

  // Print the bottom border with corners
  printf("╚");
  for (int i = 0; i < a->maxWidth - 2; i++) {
    printf("═");
  }
  printf("╝\n");
}

void move(int x, int y) {
  int termRows, termCols;

  // Get the terminal size dynamically
  getTerminalSize(&termRows, &termCols);

  // Ensure x and y are within the bounds of the terminal window
  if (x < 1)
    x = 1;
  if (x > termCols)
    x = termCols;
  if (y < 1)
    y = 1;
  if (y > termRows)
    y = termRows;

  // Move the cursor using the ANSI escape sequence
  printf("\033[%d;%dH", y, x);
  fflush(stdout);
}

void getTerminalSize(int *rows, int *cols) {
  char buffer[32];
  FILE *fp = popen("stty size", "r");
  if (fp) {
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "%d %d", rows, cols);
    fclose(fp);
  } else {
    *rows = 24;
    *cols = 80;
  }
}

void deinitsrc() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    printf("tcgetattr");
  }
}

void initsrc() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    printf("tcgetattr\n");
  }
  // atexit(deinitsrc);
  //
  struct termios raw = orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | IGNBRK | PARMRK |
                   INLCR | IGNCR);
  raw.c_oflag &= ~(OPOST); // Disable output post-processing
  raw.c_cflag |= (CS8);    // Set character size to 8 bits
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG | ECHONL);

  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  if (tcgetattr(STDIN_FILENO, &raw) == -1) {
    printf("tcgetattr\n");
  }
}
