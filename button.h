#pragma once
#include <stdbool.h>

typedef struct {
  int width, height, x, y;
  char *label;
  bool pressed;
} Button;

void drawButton(Button *btn);
int isButtonClicked(Button *btn, int mouseX, int mouseY);
