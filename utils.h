#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void clear_terminal() {
  printf("\e[1;1H\e[2J");
}

int random_int(int min, int max) {
  return min + rand() % (max+1 - min);
}

#endif
