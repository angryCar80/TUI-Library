#include "button.h"
#include "graphics.h"
#include <stdbool.h>
#include <unistd.h>

typedef enum {
  NORMAL,
  INSERT,
  VISUAL, // TODO: make the visual mode
} modes_t;

App a = {
    .maxWidth = 50,
    .maxHeight = 20,
    .title = "Notes App",
    .x = 10,
    .y = 10,
};
Button btn = {
    .height = 10,
    .width = 10,
    .x = 37,
    .y = 15,
    .label = "Click Me!",
    .pressed = false,
};

int main() {
  modes_t userMode = NORMAL;
  int mouseY = 3;
  int mouseX = 3;
  // ENABLING RAW MODE
  initsrc();
  // CLEARING THE SCREEN
  clear();
  // DRAWING THE MAIN BORDER AND BUTTON
  DrawBorder(&a);
  drawButton(&btn);
  while (true) {
    move(mouseX, mouseY);

    switch (userMode) {
    case NORMAL:
      initsrc();
      break;
    case INSERT:
      deinitsrc();
      break;
    case VISUAL:
      // TODO: DOINT LATER
      break;
    }

    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) {
      continue;
    }
    if (c == 'q') {
      deinitsrc();
      clear();
      break;
    } else if (c == 'i') {
      userMode = INSERT;
      deinitsrc();
    } else if (c == '\n') {
      if (mouseY < a.maxHeight - 1) {
        mouseY++;
      }
    } else if (c == '\x1b') {
      userMode = NORMAL;
      deinitsrc();
      // TODO: READ MOVINENT KEYS
    }
  }
  return 0;
}
