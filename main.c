#include "graphics.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

typedef enum {
  NORMAL,
  INSERT,
  VISUAL, // not implemented yet
} modes_t;

App a = {
    .maxWidth = 70,
    .maxHeight = 20,
    .title = "Notes App",
    .x = 10,
    .y = 10,
};

int main(void) {
  modes_t userMode = NORMAL;

  int cursorX = 2;
  int cursorY = 3;

  /* Enable raw mode ONCE */
  initsrc();
  clear();
  DrawBorder(&a);

  while (true) {
    move(cursorX, cursorY);

    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) {
      continue;
    }

    if (userMode == NORMAL) {
      if (c == 'q') {
        break;
      } else if (c == 'i') {
        userMode = INSERT;
      }
    } else if (userMode == INSERT) {
      if (c == 27) { // ESC key
        userMode = NORMAL;
      } else if (c == '\n') {
        if (cursorY < a.maxHeight - 1) {
          cursorY++;
          cursorX = 1;
        }
      } else {
        putchar(c);
        cursorX++; // this is the problem

        if (cursorX >= a.maxWidth - 1) {
          cursorX = 1;
          cursorY++;
        }
      }
    }
  }

  /* Restore terminal ONCE */
  deinitsrc();
  clear();
  return 0;
}
