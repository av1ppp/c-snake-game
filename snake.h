#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <ncurses.h>

#include "config.h"

typedef enum {
  TOP, RIGHT, BOTTOM, LEFT
} Direction;

Direction snake_direction;

char SNAKE_HEAD_CHAR = 'O';
char SNAKE_BODY_CHAR = '+';

typedef enum {
  SNAKE_HEAD,
  SNAKE_BODY

} SnakeKind;

typedef struct SnakeSegment SnakeSegment;
struct SnakeSegment {
  int x, y;
  SnakeKind kind;
  SnakeSegment *next;
};

typedef struct {
  SnakeSegment *head;
  unsigned length;

} Snake;

SnakeSegment *alloc_snake_segment(SnakeKind kind) {
  SnakeSegment *segment = (SnakeSegment *)malloc(sizeof(SnakeSegment));
  segment->kind = kind;
  return segment;
}

Snake *create_snake(int x, int y) {
  Snake *snake;
  SnakeSegment *head, *body_1, *body_2;

  snake = (Snake *)malloc(sizeof(Snake));
  head = alloc_snake_segment(SNAKE_HEAD);
  body_1 = alloc_snake_segment(SNAKE_BODY);
  body_2 = alloc_snake_segment(SNAKE_BODY);

  body_2->x = x+2;
  body_2->y = y;

  body_1->x = x+1;
  body_1->y = y;
  body_1->next = body_2;

  head->x = x;
  head->y = y;
  head->next = body_1;

  snake->head = head;

  return snake;
}

void move_snake(Snake *snake, int vx, int vy) {
  int tmp;

  int track_x = snake->head->x;
  int track_y = snake->head->y;

  // move x
  if (snake->head->x + vx <= 0) {
    snake->head->x = WIDTH-1;
  } else if (snake->head->x + vx >= WIDTH) {
    snake->head->x = 1;
  } else {
    snake->head->x += vx;
  }

  // move y
  if (snake->head->y + vy <= 0) {
    snake->head->y = HEIGHT-1;
  } else if (snake->head->y + vy >= HEIGHT) {
    snake->head->y = 1;
  } else {
    snake->head->y += vy;
  }

  SnakeSegment *seg = snake->head->next;

  while (seg) {
    tmp = seg->x;
    seg->x = track_x;
    track_x = tmp;

    tmp = seg->y;
    seg->y = track_y;
    track_y = tmp;
    
    seg = seg->next;
  }
}

int is_snake(Snake *snake, int x, int y) {
  SnakeSegment *seg = snake->head;
  while (seg) {
    if (seg->x == x && seg->y == y) {
      return 1;
    }
    seg = seg->next;
  }
  return 0;
}

int do_snake_step(Snake *snake) {
  int vx, vy;
  vx = vy = 0;

  switch (snake_direction)
  {
  case TOP:
    vy = -1;
    break;
  case RIGHT:
    vx = 1;
    break;
  case BOTTOM:
    vy = 1;
    break;
  case LEFT:
    vx = -1;
    break;
  }

  if (is_snake(snake, snake->head->x+vx, snake->head->y+vy)) {
    return 1;
  }

  move_snake(snake, vx, vy);
  return 0;
}

void *append_snake_body(Snake *snake) {
  SnakeSegment *lasts, *llasts, *nexts, *news;
  nexts = snake->head;
  news = alloc_snake_segment(SNAKE_BODY);

  while (nexts) {
    if (lasts) {
      llasts = lasts;
    }
    lasts = nexts;
    nexts = nexts->next;
  }

  if (lasts->x > llasts->x) {
    news->x = lasts->x+1;
  } else if (lasts->x < llasts->x) {
    news->x = lasts->x-1;
  } else {
    news->x = lasts->x;
  }

  if (lasts->y > llasts->y) {
    news->y = lasts->y+1;
  } else if (lasts->y < llasts->y) {
    news->y = lasts->y-1;
  } else {
    news->y = lasts->y;
  }

  lasts->next = news;
}

// SnakeSegment *last_seg = get_last_snake_segment(snake);

// SnakeSegment *new_seg = alloc_snake_segment(SNAKE_BODY);
// new_seg->x = 5;
// new_seg->y = 5;

// last_seg->next = new_seg;


// SnakeSegment *get_last_snake_segment(Snake *snake) {
//   SnakeSegment *seg = snake->head;
//   while (seg) {
//     seg = seg->next;
//   }
//   return seg;
// }

#endif