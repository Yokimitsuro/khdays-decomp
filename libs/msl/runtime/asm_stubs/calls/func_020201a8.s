/* _ll_mod (func_020201a8) -- CodeWarrior runtime assembly: signed 64-bit remainder: flags the dividend sign and joins _ll_sdiv's common body. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_020201a8
    .type func_020201a8, %function
    .global _ll_mod
    .type _ll_mod, %function
func_020201a8:
_ll_mod:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, r1
    orr r4, r4, #1
    b label_020201c8
    .size func_020201a8, .-func_020201a8
