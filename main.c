#include "button.h"
#include "graphics.h"
#include <stdbool.h>

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
    .x = 10,
    .y = 10,
    .label = "Press Me",
    .pressed = false,
};

int main() {
  initsrc();
  clear();
  DrawBorder(&a);
  drawButton(&btn);
  while (true) {
    move(3, 3);
    char c;
    if (c == 'q') {
      clear();
      break;
    }
  }
  return 0;
}
