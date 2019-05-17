/* Alex Moore (alex9)
 * CPSC 2310 Sec 001
 * Program3
 * 4/2/18
 *
 * Program does the math to compute the square of a number
 * X+1 given X and X^2
 */

 /* Function name: nextsquare
    description: Program does the math to compute the square of a number
                 X+1 given X and X^2
    input parameters:
      r0 - X
      r1 - X^2
    return value:
      (X+1)^2
    Other output parameters:
      none
    effect/output
      none apart from return value

  */

    .global nextsquare

nextsquare:
    push {lr}

    add r2, r0, #1 //r2 = r0 + 1
    add r0, r0, r2 //r0 = r0 + r2
    add r0, r0, r1 //r0 = r0 + r1

    pop {pc}
