#include <stdio.h>

int nextsquare (int r0, int r1) {
  int r2 = 0;
  r2 = r0 + 1;
  r0 = r0 + r2;
  r0 = r0 + r1;

  return r0;
}
