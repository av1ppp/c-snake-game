// sudo apt-get install libncursesw5-dev

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>

#include "config.h"
#include "snake.h"
#include "apple.h"

Snake *snake;
Apple *apple;

int score = 0;

void init() {
  // Use current time as seed for random generator
  srand(time(0));

  snake = create_snake(WIDTH/2, HEIGHT/2);
  apple = create_apple_random_pos(WIDTH, HEIGHT);
  snake_direction = LEFT;
}

int start_game();
void render_game_field();
void render_score();
void snake_eat_apple();


//=============================================================================

int main(int argc, char **argv)
{
  int ch;
  setlocale(LC_ALL, "");

  init();
  initscr();      // Переход в curses-режим
  noecho();       // Не выводим нажатые клавиши
  halfdelay(2.5); // Ожидание нажатия в 500мс.
  curs_set(0);    // Отключаем курсора.

  while (1) {
    if (do_snake_step(snake) != 0) {
      break;
    }
    if (is_apple(apple, snake->head->x, snake->head->y)) {
      snake_eat_apple();
    }

    switch ((ch = getch()))
    {
    case 52:
    case 104: // h
      if (snake_direction != RIGHT)
        snake_direction = LEFT;
      break;

    case 53:
    case 106: // j
      if (snake_direction != TOP)
        snake_direction = BOTTOM;
      break;

    case 56:
    case 107: // k
      if (snake_direction != BOTTOM)
        snake_direction = TOP;
      break;

    case 54:
    case 108: // l
      if (snake_direction != LEFT)
        snake_direction = RIGHT;
      break;
    }

    // printw("%d\n", ch);
    // refresh();
    // exit(1);


    clear();
    render_game_field();
    render_score();
    refresh();

    // clear_terminal();

    // usleep(300000);
  }

  return endwin(); // Выход из curses-режима.
}

//=============================================================================

void snake_eat_apple() {
  apple = create_apple_random_pos();
  append_snake_body(snake);
  score++;
}



void render_score() {
  printw("Your score: %d", score);
}

void render_game_field()
{
  int x, y;
  SnakeSegment *ssegment = snake->head;

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      // Draw border
      if (y == 0 || y == HEIGHT-1) {
        addch('-');
        continue;
      } 
      if (x == 0 || x == WIDTH-1) {
        addch('|');
        continue;
      } 

      // Draw apple
      if (apple->x == x && apple->y == y) {
        printw("%c", APPLE_CHAR);
        continue;
      }

      // Draw snake
      while (ssegment) {
        // printf("%d-%d %d-%d\n", x, y, ssegment->x, ssegment->y);
        if (ssegment->x == x && ssegment->y == y) {
          printw("%c", ssegment->kind == SNAKE_HEAD ? SNAKE_HEAD_CHAR : SNAKE_BODY_CHAR);
          break;
        }
        ssegment = ssegment->next;
      }
      if (!ssegment) { // если не был найден - пустота
        printw(" ");
      }
      ssegment = snake->head;
    }
    printw("\n");
  }
}
