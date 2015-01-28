#ifndef SNAKE_H
#define SNAKE_H

#include "pos.h"

#define SNAKE_MAX_LENGTH 100

typedef struct {
  POS cell[SNAKE_MAX_LENGTH];
  int riemp;
  int dir;    /* direzione: 0 (alto), 1 (sinistra), 2 (basso), 3 (destra) */
} SNAKE;

void snake_dump(SNAKE *snake);
void snake_init(SNAKE *snake);
void snake_print(SNAKE *snake);
void snake_unprint(SNAKE *snake);
POS snake_get_head_pos(SNAKE *snake);
POS* snake_get_cell(SNAKE *snake, int index);
void snake_set_cell(SNAKE *snake, int index, POS *p);
int snake_get_len(SNAKE *snake);
int snake_get_direction(SNAKE *snake);
void snake_set_direction(SNAKE *snake, int dir);
int snake_zeroed(SNAKE *snake);
int snake_eat_itself(SNAKE *snake);
int snake_wall_impact(SNAKE *snake, int screen_x, int screen_y);
void snake_update_pos(SNAKE *snake);
int snake_pos_in(SNAKE *snake, POS *p);
void snake_grow(SNAKE *snake);
void snake_shrink(SNAKE *snake);

#endif
