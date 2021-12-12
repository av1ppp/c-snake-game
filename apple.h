#ifndef APPLE_H
#define APPLE_H

#include <stdlib.h>

#include "utils.h"

char APPLE_CHAR = '@';

typedef struct {
  int x, y;
} Apple;

Apple *create_apple(int x, int y) {
  Apple *apple = (Apple *)malloc(sizeof(Apple));
  apple->x = x;
  apple->y = y;
  return apple;
}

Apple *create_apple_random_pos() {
  int x = random_int(2, WIDTH-2);
  int y = random_int(2, HEIGHT-2);
  return create_apple(x, y);
}

int is_apple(Apple *apple, int x, int y) {
  return apple->x == x && apple->y == y;
}

#endif
