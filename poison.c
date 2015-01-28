#include "pos.h"
#include "poison.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void poison_age(POISON *p);
int poison_random_type();
int poison_random_character(int type);
int poison_random_life();
POS poison_random_pos();

void poison_dump(POISON *p)
{
  printf("type: %d\n", p->type);
  printf("char: %c\n", p->character);
  printf("life: %d\n", p->life);
  printf("pos: "); pos_print(&p->position); putchar('\n');
  printf("active: %d\n", p->active);
}

void poison_init(POISON *p, int size)
{
  srand(time(NULL));
  
  int i;
  for (i=0; i<size; i++) {
    (*(p+i)).active = 0;
  }
}

int poison_num_free_slot(POISON *p, int size)
{
  int i;
  int counter = 0;
  
  for (i=0; i<size; i++) {
    if ((*(p+i)).active==0) {
      counter++;
    }
  }
  
  return counter;
}

int poison_can_create(POISON *p, int size)
{
  int i;
  
  for (i=0; i<size; i++) {
    if ((*(p+i)).active==0) {
      return i;
    }
  }

  return -1;
}



void poison_destroy(POISON *p)
{
  p->active = 0;
  mvaddch(p->position.y, p->position.x, ' ');
}

void poison_print(POISON *p)
{
  mvaddch(p->position.y, p->position.x, p->character);
}

void poison_oldfy(POISON *p, int size)
{
  int i;
  for (i=0; i<size; i++) {
    if ((*(p+i)).active) {
      poison_age(p+i);
    }
  }
}

void poison_age(POISON *p)
{
  p->life--;
  if (p->life<=0) poison_destroy(p);
}

void poison_create(POISON *p, SNAKE *snake, int screen_x, int screen_y)
{
  p->type = poison_random_type();
  p->character = poison_random_character(p->type);
  p->life = poison_random_life();
  p->position = poison_random_pos(snake, screen_x, screen_y);
  p->active = 1;
}

int poison_random_type()
{
  return rand()%2;
}

int poison_random_character(int type)
{
  char poisons[2][3] = {
    {'x', 'w', '*'},  /* poisons */
    {'o', '&', 'O'}   /* fruits */
  };
  /* scegli in poisons[type] */
  int size = 3; /*sizeof(poisons[type][])/sizeof(char);*/
  return poisons[type][rand()%size];
}

int poison_random_life()
{
  return (20+rand()%80);
}

POS poison_random_pos(SNAKE *snake, int screen_x, int screen_y)
{
  POS p;
  
  do {
    p.x = 1+rand()%(screen_x-2);
    p.y = 1+rand()%(screen_y-2);
  } while(snake_pos_in(snake, &p));
  
  return p;
}
