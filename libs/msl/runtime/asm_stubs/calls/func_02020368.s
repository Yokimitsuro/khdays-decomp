/* _ll_udiv (func_02020368) -- CodeWarrior runtime assembly: unsigned 64-bit division: joins _ull_mod's body with the quotient selected. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_02020368
    .type func_02020368, %function
    .global _ll_udiv
    .type _ll_udiv, %function
func_02020368:
_ll_udiv:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, #0
    b label_0202037c
    .size func_02020368, .-func_02020368
