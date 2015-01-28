#ifndef POS_H
#define POS_H

typedef struct {
  int x;
  int y;
} POS;

int pos_equals(POS *p1, POS *p2);
void pos_print(POS *p);

#endif
