#include "button.h"
#include <stdio.h>

void drawButton(Button *btn) {
  printf("\033[%d;%dH", btn->y, btn->x);
  printf("[ ");
  printf("%-*s", btn->width - 4, btn->label);
  printf(" ]");
}
int isButtonClicked(Button *btn, int mouseX, int mouseY) {
  if (mouseX >= btn->x && mouseX <= btn->x + btn->width && mouseY >= btn->y &&
      mouseY <= btn->y + btn->height) {
    return 1;
  }
  return 0;
}
