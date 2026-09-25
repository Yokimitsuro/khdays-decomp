/* _ll_sdiv (func_020201b8) -- CodeWarrior runtime assembly: signed 64-bit division (r0:r1 / r2:r3); a 32-bit case goes through _s32_div_f. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_020201b8
    .type func_020201b8, %function
    .global _ll_sdiv
    .type _ll_sdiv, %function
func_020201b8:
_ll_sdiv:
    push {r4, r5, r6, r7, fp, ip, lr}
    eor r4, r1, r3
    asr r4, r4, #1
    lsl r4, r4, #1
    .global label_020201c8
label_020201c8:
    orrs r5, r3, r2
    bne .L_020201d8
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_020201d8:
    lsr r5, r0, #0x1f
    add r5, r5, r1
    lsr r6, r2, #0x1f
    add r6, r6, r3
    orrs r6, r5, r6
    bne .L_0202020c
    mov r1, r2
    bl func_02020400
    ands r4, r4, #1
    movne r0, r1
    asr r1, r0, #0x1f
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_0202020c:
    cmp r1, #0
    bge .L_0202021c
    rsbs r0, r0, #0
    rsc r1, r1, #0
.L_0202021c:
    cmp r3, #0
    bge .L_0202022c
    rsbs r2, r2, #0
    rsc r3, r3, #0
    .global label_0202022c
label_0202022c:
.L_0202022c:
    orrs r5, r1, r0
    beq .L_02020350
    mov r5, #0
    mov r6, #1
    cmp r3, #0
    bmi .L_02020258
.L_02020244:
    add r5, r5, #1
    adds r2, r2, r2
    adcs r3, r3, r3
    bpl .L_02020244
    add r6, r6, r5
.L_02020258:
    cmp r1, #0
    blt .L_02020278
.L_02020260:
    cmp r6, #1
    beq .L_02020278
    sub r6, r6, #1
    adds r0, r0, r0
    adcs r1, r1, r1
    bpl .L_02020260
.L_02020278:
    mov r7, #0
    mov ip, #0
    mov fp, #0
    b .L_020202a0
.L_02020288:
    orr ip, ip, #1
    subs r6, r6, #1
    beq .L_020202f8
    adds r0, r0, r0
    adcs r1, r1, r1
    adcs r7, r7, r7
.L_020202a0:
    subs r0, r0, r2
    sbcs r1, r1, r3
    sbcs r7, r7, #0
    adds ip, ip, ip
    adc fp, fp, fp
    cmp r7, #0
    bge .L_02020288
.L_020202bc:
    subs r6, r6, #1
    beq .L_020202f0
    adds r0, r0, r0
    adcs r1, r1, r1
    adc r7, r7, r7
    adds r0, r0, r2
    adcs r1, r1, r3
    adc r7, r7, #0
    adds ip, ip, ip
    adc fp, fp, fp
    cmp r7, #0
    bge .L_02020288
    b .L_020202bc
.L_020202f0:
    adds r0, r0, r2
    adc r1, r1, r3
.L_020202f8:
    ands r7, r4, #1
    moveq r0, ip
    moveq r1, fp
    beq .L_02020330
    subs r7, r5, #0x20
    lsrge r0, r1, r7
    bge .L_02020354
    rsb r7, r5, #0x20
    lsr r0, r0, r5
    orr r0, r0, r1, lsl r7
    lsr r1, r1, r5
    b .L_02020330
    lsr r0, r1, r7
    mov r1, #0
.L_02020330:
    cmp r4, #0
    blt .L_02020340
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_02020340:
    rsbs r0, r0, #0
    rsc r1, r1, #0
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_02020350:
    mov r0, #0
.L_02020354:
    mov r1, #0
    cmp r4, #0
    blt .L_02020340
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
    .size func_020201b8, .-func_020201b8
