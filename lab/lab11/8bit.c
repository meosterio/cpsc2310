/* Alex Moore
   CPSC 2311 Sec 3
   Lab 11
*/

#include <stdio.h>
#include <math.h>

int main()
{
  int sign, exp, fraction, significand;
  int i;
  float f;
  float prev = 0;

  for (i = 0; i < 256; i++)
  {
    /* begin your code */
    sign = (i>>7)&1;
    exp = (i>>3)&15;
    fraction = (i&7);

    int denormal = 0;
    if (exp == 0) {
      denormal = 1;
      exp = 1;
    }
    exp -= 8;

    if(denormal == 1) {
      significand = (0|fraction);
    }
    else  {
      significand = (8|fraction);
    }

    exp -= 3;

    f = significand;
    f = f * pow(2, exp);
    if (sign == 1) {
      f = -f;
    }
    //./a.out > result.text
    //diff output result.txt

    /* end your code */

    printf ("%02x => %08x = %+11.6f (spacing = %+11.6f)\n",
            i, *(int*) &f, f, prev-f);
    prev = f;
  }

  return 0;
}
