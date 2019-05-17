/* Alex Moore
   CPSC 2311 Sec 3
   Lab 7
*/

	.global	fact
fact:
    push  {r1, lr}        @ //push r1 and lr onto the stack

    cmp   r0, #1          @ //compare the value in r0 to 1
    beq   done            @ //if r0 is equal to 1, branch to done

    mov  r1, r0           @ //mov the value in r0 to r1
    sub  r0, r0, #1       @ //sub 1 from the value in r0 and put the ans in r0
    bl   fact             @ //branch and link the value in r1 back into fact

    mul  r0, r1, r0       @ //multiply r0 and r1 and store the value in r0

done:
    pop  {r1, pc}         @ //pop r1 and pc from the stack
    .size    fact, .-fact

    .align   2
    .section .rodata
fmt_str:
    .ascii   "The factorial of %d is %d\012\000"

    .text
    .align   2
    .global  main
main:
    push {lr}             @ save the link register so we can jump back to

    @ MAIN CODE GOES HERE
		mov r0, #10
		bl fact
		mov r2, r0
		mov r1, #10
		ldr r0, =fmt_str
		bl printf

    pop  {pc}             @ pop the top of the stack

	.size    main, .-main
	.ident   "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section .note.GNU-stack,"",%progbits
