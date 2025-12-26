#pragma once
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
  int maxWidth;
  int maxHeight;
  char *title;
  int x, y;
} App;

void clear();
void DrawBorder(App *a);
void DrawTextBox(App *a, int x, int y);
void printBox(int width, int height);
void move(int x, int y);
void initsrc();
void deinitsrc();
void raw();
