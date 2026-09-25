/* _ll_shl (func_020203d0) -- CodeWarrior runtime assembly: 64-bit shift left of r0:r1 by r2 (mod 64). */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_020203d0
    .type func_020203d0, %function
    .global _ll_shl
    .type _ll_shl, %function
func_020203d0:
_ll_shl:
    ands r2, r2, #0x3f
    bxeq lr
    subs r3, r2, #0x20
    bge .L_020203f4
    rsb r3, r2, #0x20
    lsl r1, r1, r2
    orr r1, r1, r0, lsr r3
    lsl r0, r0, r2
    bx lr
.L_020203f4:
    lsl r1, r0, r3
    mov r0, #0
    bx lr
    .size func_020203d0, .-func_020203d0
