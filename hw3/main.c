#include <stdio.h>

int main (void) {

  int r5 = 0;
  int r6 = 0;
  int r4;
  int r0;
  int r1;
  int r2 = 2;
  printf("Enter an integer greater than 0: ");
  scanf("%d", &r4);

  while (r5 < 5) {
    r5+=1;
    r0 = r4;
    r6 = r4*r4;
    r1 = r6;
    r0 = nextsquare(r0, r1);
    r4 +=1;
    r1 = r4;
    printf("%d^%d = %d\n", r1, r2, r0);
  }

  return 0;
}
