/* Alex Moore
   CPSC 2311 Sec 3
   Lab 6
*/

	.global main

main:
	push {r7, lr}
	sub sp, sp, #16
	add r7, sp, #0

	ldr r0, =0x12345678       /* put the source value in r0 */
	/*     0001 0010 0011 0100 0[101 0110 0]111 1000, 0xAC */
	ldr r2, =0x7              /* put the location of the field's lsb in r2 */
	ldr r3, =0x8              /* put the size of field in r3 */

/* Beginning of your code */

ldr r1, =0x1				/* put 0001 in r1 */
lsl r1, r1, r3			/* shift r1 left by r3 */
sub r1, r1, #1			/* subtract 1 */
lsr r4, r0, r2			/* shift r0 right by r2 */
and r1, r1, r4			/* and r1 and r4, store result in r1 */

/* End of your code */

/* show output on screen */
    ldr r0, =prt_line
	bl printf
	add r7, r7, #16
	mov sp, r7
	pop {r7, pc}

	.size main, .-main
	.section .rodata

prt_line: .asciz "0x%X\n"
