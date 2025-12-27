#pragma once
// Text Colors
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

// Background colors
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_BLUE "\x1b[44m"

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
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

// BASIC TUI APP
void initsrc();
void deinitsrc();
void die(const char *s);

// Diplaying Functions
void clear();
// Drawing Functions
void DrawBorder(App *a);
void DrawTextBox(App *a, int x, int y);
void raw();
void move(int x, int y);

void getTerminalSize(int *row, int *cols);
