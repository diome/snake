#include "pos.h"
#include <stdio.h>

int pos_equals(POS *p1, POS *p2)
{
  return (p1->x==p2->x && p1->y==p2->y);
}

void pos_print(POS *p)
{
  printf("(%d, %d)", p->x, p->y);
}
