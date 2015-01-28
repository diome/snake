#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "pos.h"
#include "snake.h"
#include "poison.h"

#define MAX_POISON 10

void print_walls(int screen_x, int screen_y);
int is_time_to_add_a_poison();

void snake_eat_poison(SNAKE *snake, POISON *poison, int size);

int main()
{
  clock_t start, end;
  int elapsed;
  int ch;
  
  srand(time(NULL));

  SNAKE snake;
  snake_init(&snake);
  snake_dump(&snake);
  
  POISON poison[MAX_POISON];
  poison_init(poison, MAX_POISON);
  printf("poison num free slot: %d (expect %d)\n", poison_num_free_slot(poison, MAX_POISON), MAX_POISON);
  
  int poison_index;
  
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);

  int screen_x, screen_y;
  getmaxyx(stdscr, screen_y, screen_x);

  print_walls(screen_x, screen_y);
  
  while(1) {
    start = clock();

    ch = getch();
    switch(ch) {
      case 'h':
        snake_set_direction(&snake, 1);
        break;
      case 'j':
        snake_set_direction(&snake, 2);
        break;
      case 'k':
        snake_set_direction(&snake, 0);
        break;
      case 'l':
        snake_set_direction(&snake, 3);
        break;
    }

    snake_unprint(&snake);
    snake_update_pos(&snake);
    if (is_time_to_add_a_poison()) {
      poison_index = poison_can_create(poison, MAX_POISON);
      if (poison_index!=-1) {
        poison_create(poison+poison_index, &snake, screen_x, screen_y);
        poison_print(poison+poison_index);refresh();
      }
    }
    snake_print(&snake);
    refresh();
    
    if (snake_zeroed(&snake)) break;
    if (snake_eat_itself(&snake)) break;
    if (snake_wall_impact(&snake, screen_x, screen_y)) break;
    
    snake_eat_poison(&snake, poison, MAX_POISON);
    
    poison_oldfy(poison, MAX_POISON);

    end = clock();
    elapsed = (double)(end-start)/CLOCKS_PER_SEC * 1000;

    napms(200-elapsed);
  }

  endwin();
  poison_dump(poison);
  
  printf("screen: %dx%d\n", screen_x, screen_y);
  printf("elapsed: %d\n", elapsed);

  return 0;
}

void print_walls(int screen_x, int screen_y)
{
  int i;

  /* top wall */
  for (i=0; i<screen_x; i++) {
    mvaddch(0, i, '#');
  }
  /* bottom wall */
  for (i=0; i<screen_x; i++) {
    mvaddch(screen_y-1, i, '#');
  }
  /* left wall */
  for (i=0; i<screen_y; i++) {
    mvaddch(i, 0, '#');
  }
  /* right wall */
  for (i=0; i<screen_y; i++) {
    mvaddch(i, screen_x-1, '#');
  }
}

int is_time_to_add_a_poison()
{
  return (rand()%100 < 5);
}

void snake_eat_poison(SNAKE *snake, POISON *poison, int size)
{
  POS snake_head_pos = snake_get_head_pos(snake);
  int i;
  
  for (i=0; i<size; i++) {
    if ((*(poison+i)).active) {
      if (pos_equals(&snake_head_pos, &((*(poison+i)).position))) {
        if ((*(poison+i)).type==0) {
          snake_shrink(snake);
        } else {
          snake_grow(snake);
        }
        poison_destroy(poison+i);
      }
    }
  }
}
