#include "pos.h"
#include "snake.h"
#include "ncurses.h"

void snake_dump(SNAKE *snake)
{
  int i;
  POS *current;

  for (i=0; i<snake_get_len(snake); i++) {
    current = snake_get_cell(snake, i);
    printf("[%d]: (%d, %d)\n", i, current->x, current->y);
  }
  printf("\n");
}

void snake_init(SNAKE *snake)
{
  POS start = { 20, 10 };

  snake->riemp = 10;
  snake->cell[0] = start;
  int i;
  for (i=snake->riemp-1; i>0; i--) {
    snake->cell[i].x = snake->cell[0].x;
  }
  for (i=1; i<snake->riemp; i++) {
    snake->cell[i].y = snake->cell[i-1].y-1;
  }

  snake->dir = 2;
}

void snake_print(SNAKE *snake)
{
  POS current = snake_get_head_pos(snake);
  mvaddch(current.y, current.x, '@');

  int i;
  for (i=1; i<snake_get_len(snake); i++) {
    current = *(snake_get_cell(snake, i));
    mvaddch(current.y, current.x, 'm');
  }
}

void snake_unprint(SNAKE *snake)
{
  POS current;
  int i;
  for (i=0; i<snake_get_len(snake); i++) {
    current = snake->cell[i];
    mvaddch(current.y, current.x, ' ');
  }
}

POS snake_get_head_pos(SNAKE *snake)
{
  return snake->cell[0];
}

POS* snake_get_cell(SNAKE *snake, int index)
{
  return &snake->cell[index];
}

void snake_set_cell(SNAKE *snake, int index, POS *p)
{
  snake->cell[index].x = p->x;
  snake->cell[index].y = p->y;
}

int snake_get_len(SNAKE *snake)
{
  return snake->riemp;
}

int snake_get_direction(SNAKE *snake)
{
  return snake->dir;
}

void snake_set_direction(SNAKE *snake, int dir)
{
  snake->dir = dir;
}

int snake_zeroed(SNAKE *snake)
{
  return snake_get_len(snake)<=2;
}

int snake_eat_itself(SNAKE *snake)
{
  POS head = snake_get_head_pos(snake);
  int i;
  for (i=1; i<snake_get_len(snake); i++) {
    if (pos_equals(&head, snake_get_cell(snake, i))) {
      return 1;
    }
  }
  return 0;
}

int snake_wall_impact(SNAKE *snake, int screen_x, int screen_y)
{
  POS head = snake_get_head_pos(snake);

  if (head.x==0 || head.x==screen_x-1 ||
    head.y==0 || head.y==screen_y-1)
    return 1;

  return 0;
}

void snake_update_pos(SNAKE *snake)
{
  int dx, dy;
  
  switch(snake_get_direction(snake)) {
    case 0:
      dx = 0;
      dy = -1;
      break;
    case 1:
      dx = -1;
      dy = 0;
      break;
    case 2:
      dx = 0;
      dy = 1;
      break;
    case 3:
      dx = 1;
      dy = 0;
      break;
  }

  POS head = snake_get_head_pos(snake);
  head.x += dx;
  head.y += dy;

  int i;
  for (i=snake_get_len(snake)-2; i>=0; i--) {
    snake_set_cell(snake, i+1, snake_get_cell(snake, i));
  }
  snake_set_cell(snake, 0, &head);
}

int snake_pos_in(SNAKE *snake, POS *p)
{
  int i;
  POS *cell;
  
  for (i=0; i<snake_get_len(snake); i++) {
    cell = snake_get_cell(snake, i);
    if (pos_equals(cell, p)) return 1;
  }
  
  return 0;
}

void snake_grow(SNAKE *snake)
{
  snake->riemp++;
}

void snake_shrink(SNAKE *snake)
{
  snake_unprint(snake);
  snake->riemp--;
}
