/* Alex Moore
   CPSC 2311 Sec 3
   Lab 7
*/

	.global	fact
fact:
	mov   r1, #1       @ //set r1 to 1

here:
	cmp   r0, #1       @  //compare the value in r0 to 1
	beq   there        @  //if r0 is equal to 1, branch to there

	mul   r1, r0, r1   @  //multiply r0 and r1 and store the value in r1
	sub   r0, r0, #1   @  //sub 1 from the value in r0 and put the answer in r0
	b     here         @  //branch to here always

there:
	mov   r0, r1       @	//mov the value in r1 to r0

	bx    lr

	.size	fact, .-fact

	.align   2
	.section .rodata
fmt_str:
	.ascii  "The factorial of %d is %d\012\000"

	.text
	.align  2
	.global main
main:
	push  {lr}

	@ MAIN CODE GOES HERE
	mov r0, #10
	bl fact
	mov r2, r0
	mov r1, #10
	ldr r0, =fmt_str
	bl printf

	pop  {pc}

	.size    main, .-main
	.ident   "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section .note.GNU-stack,"",%progbits
