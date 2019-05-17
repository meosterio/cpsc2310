/* Alex Moore
   CPSC 2311 Sec 3
   Lab 8
*/

    .file "sum.s"
    .text
    .align  2
    .global main
    .type   main, %function

/* main() sums 10 values from stdin and prints the sum */
main:
    push {lr}    // save lr

    //Code goes here
    sub sp, sp, #40 //make room on the stack
    mov r4, sp
    mov r5, #0 //i = 0
    mov r6, #0 //sum is 0
loop1:
    ldr r0, =rdfmt  //put %d in r0
    mov r1, r4      //move the location to r1
    bl scanf        //read in the next value
    add r4, r4, #4  //add 4 to prepare the next location
    add r5, r5, #1  //add 1 to r5
    cmp r5, #10     //loop while r5 < 10
    blt loop1

    mov r4, sp
    mov r5, #0 //i = 0

loop2:
    ldr r2, [r4]
    add r4, r4, #4
    add r6, r6, r2  //add r2 to r6
    add r5, r5, #1  //sub 1 from r5
    cmp r5, #10     //loop while r5 < 10
    blt loop2

    ldr r0, =prtfmt //put the print statement in r0
    mov r1, r6      //move the computed sum to r1
    bl printf       //print the sum

    add sp, sp, #40

    pop {pc}         // put lr in pc

.section    .rodata
    rdfmt:        .asciz "%d"
    prtfmt:       .asciz "sum is %d\n"
