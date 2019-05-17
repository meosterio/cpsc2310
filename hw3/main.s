/* Alex Moore (alex9)
 * CPSC 2310 Sec 001
 * Program3
 * 4/2/18
 *
 * Program to compute the next 5 squares of a number given by the user
 */

    .file "main.s"
    .text
    .align  2
    .global main
    .type   main, %function

main:
    push {lr}

    sub sp, sp, #4  //make room on the stack
    mov r5, #0 //i = 0
    mov r6, #0 //X^2 holder

    ldr r0, =string
    bl printf

    ldr r0, =rdfmt
    mov r1, sp //location to put the users value for X
    bl scanf

    ldr r4, [sp] //X, load the value from the stack

loop:
    add r5, r5, #1 //i++
    mov r0, r4     //put X in r0
    mul r6, r4, r4 //X^2
    mov r1, r6     //put X^2 in r1
    bl nextsquare

    add r4, r4, #1

    mov r1, r4
    mov r2, #2
    mov r3, r0
    ldr r0, =prtfmt
    bl printf
    cmp r5, #5 //while r5 < 5, loop
    blt loop

    add sp, sp, #4 //return the stack pointer
    pop {pc}

.section    .rodata
  rdfmt:        .asciz "%d"
  string:       .asciz "Enter an integer greater than 0: "
  prtfmt:       .asciz "%d^%d = %d\n"
