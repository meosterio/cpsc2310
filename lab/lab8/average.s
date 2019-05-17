/* Alex Moore
   CPSC 2311 Sec 3
   Lab 8
*/

  .file "average.s"
  .text
  .align  2
  .global main
  .type   main, %function

/* main() sums 16 values from stdin and prints the average */
main:
  push {lr}    // save lr

  //Code goes here
  sub sp, sp, #64 //make room on the stack
  mov r4, sp
  mov r5, #0 //i = 0
  mov r6, #0 //sum = 0
loop1:
  ldr r0, =rdfmt  //put %d in r0
  mov r1, r4      //move the location to r1
  bl scanf        //read in the next value
  add r4, r4, #4  //add 4 to prepare the next location
  add r5, r5, #1  //add 1 to r5
  cmp r5, #16     //loop while r5 < 16
  blt loop1

  mov r4, sp
  mov r5, #0

loop2:
  ldr r2, [r4]
  add r4, r4, #4
  add r6, r6, r2  //add r2 to r6
  add r5, r5, #1  //sub 1 from r5
  cmp r5, #16     //loop while r5 < 16
  blt loop2

  ldr r0, =prtfmt   //put the print statement in r0
  mov r1, r6        //move the computed sum to r1
  asr r1, r1, #4    //divide by 16
  bl printf         //print the average

  add sp, sp, #64

  pop {pc}         // put lr in pc

.section    .rodata
  rdfmt:        .asciz "%d"
  prtfmt:       .asciz "average is %d\n"
