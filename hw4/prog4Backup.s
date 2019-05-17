/* Alex Moore (alex9)
 * CPSC 2310 Sec 001
 * Program4
 * 4/2/18
 *
 * Program to ......
 */

 .file "prog4.s"

.global prepareKey
.global encode
.global decode

prepareKey:
    push {r4, r5, r6, r7, r8, lr}

    mov r1, #0              //currentNewKeyIdx
    mov r2, #0              //i = 0
    sub sp, sp, #130        //make room on the stack
    add r3, sp, #26         //starting index of seenArray
    mov r7, sp              //starting index of newKey

    initialize:
        str r1, [r3, r2]
        add r2, r2, #4
        cmp r2, #104
        ble initialize

    mov r2, #0

    loop:
        ldrb r4, [r0, r2]   //char c = key[i]
        sub r5, r4, #97     //int seenIdx = c - 97
        ldrb r6, [r3, r5, lsl #2]   //r6 = seenArray[seenIdx]
        cmp r4, #0x00       //make sure char isn't eol
        beq done
        cmp r6, #0          //if (seenArray[seenIdx] == 0)
        bne past_if
        str r4, [r7, r1]    //put c in newKey
        add r1, r1, #1      //currentNewKeyIdx++
        mov r8, #1          //put 1 in seenArray
        str r8, [r3, r5, lsl #2]
    past_if:
        add r2, r2, #1      //i++
        cmp r2, #27
        blt loop
    done:

    mov r2, #0

    loop3:
        ldr r8, =alphabet
        ldrb r4, [r8, r2]   //get letter
        sub r5, r4, #97     //get seenIdx
        ldrb r6, [r3, r5, lsl #2]   //r6 = seenArray[seenIdx]
        cmp r6, #0          //if (seenArray[seenIdx] == 0)
        bne past
        strb r4, [r7, r1]   //put alphabet letter in newKey
        add r1, r1, #1      //currentNewKeyIdx++
    past:
        add r2, r2, #1
        cmp r2, #27
        blt loop3

    mov r2, #0

    loop2:                  //set key to newKey
        ldrb r8, [r7, r2]
        strb r8, [r0, r2]
        add r2, r2, #1
        cmp r2, #27
        blt loop2

    add sp, #130
    pop {r4, r5, r6, r7, r8, pc}

encode:
    push {r5-r8, lr}

    mov r3, #0
    ldr r8, =alphabet

    loop4:
        mov r7, #0
        ldrb r5, [r0, r3]
        add r3, r3, #1
        cmp r3, #60
        beq done1
    check:
        ldrb r6, [r8, r7]
        add r7, r7, #1
        cmp r5, r6
        bne check
        sub r7, r7, #1
        ldrb r6, [r1, r7]
        add r7, r7, #1
        sub r3, r3, #1
        strb r6, [r2, r3]
        add r3, r3, #1
        b loop4
    done1:

    pop {r5-r8, pc}

decode:
    push {r4, r5, r6, r7, r8, lr}

    mov r3, #0
    ldr r8, =alphabet

    loop6:
        mov r7, #0
        ldrb r5, [r0, r3]
        add r3, r3, #1
        cmp r3, #60
        beq done2
    loop7:
        ldrb r6, [r1, r7]
        add r7, r7, #1
        cmp r5, r6
        bne loop7
        sub r7, r7, #1
        ldrb r6, [r8, r7]
        add r7, r7, #1
        sub r3, r3, #1
        strb r6, [r2, r3]
        add r3, r3, #1
        b loop6
    done2:

    pop {r4, r5, r6, r7, r8, pc}

alphabet: .string "abcdefghijklmnopqrstuvwxyz "
