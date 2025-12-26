#include "graphics.h"

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
  printf("\033[%d;%dH", y, x);
  /*
    if (x > 0) {
      printf("\033[%dC", x);
    } else if (x < 0) {
      printf("\033[%dD", x);
    }
    //  Y axis
    if (y > 0) {
      printf("\033[%dA", y);
    } else if (y < 0) {
      printf("\033[%dB", y);
    }
    */
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
