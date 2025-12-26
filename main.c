#include "graphics.h"
#include <stdbool.h>
App a = {
    .maxWidth = 40,
    .maxHeight = 10,
    .title = "Notes App",
    .x = 10,
    .y = 10,
};

int main() {
  initsrc();
  clear();
  DrawBorder(&a);
  char c;
  while (true) {
    move(40 / 2 + 1, 10 / 2 + 1);
    if (c == 'q') {
      clear();
      break;
    }
  }
  return 0;
}
