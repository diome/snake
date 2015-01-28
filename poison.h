#ifndef POISON_H
#define POISON_H

#include "pos.h"
#include "snake.h"

typedef struct {
  int type;
  int character;
  int life;
  POS position;
  int active;
} POISON;

void poison_dump(POISON *p);
void poison_init(POISON *p, int size);
void poison_print(POISON *p);
int poison_num_free_slot(POISON *p, int size);
int poison_can_create(POISON *p, int size);
void poison_create(POISON *p, SNAKE *snake, int screen_x, int screen_y);
void poison_destroy(POISON *p);
void poison_oldfy(POISON *p, int size);

#endif
