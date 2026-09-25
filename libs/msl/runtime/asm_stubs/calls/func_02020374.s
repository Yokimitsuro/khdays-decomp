/* _ull_mod (func_02020374) -- CodeWarrior runtime assembly: unsigned 64-bit remainder; a 32-bit case goes through _u32_div_not_0_f. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_02020374
    .type func_02020374, %function
    .global _ull_mod
    .type _ull_mod, %function
func_02020374:
_ull_mod:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, #1
    .global label_0202037c
label_0202037c:
    orrs r5, r3, r2
    bne .L_0202038c
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_0202038c:
    orrs r5, r1, r3
    bne label_0202022c
    mov r1, r2
    bl _u32_div_not_0_f
    cmp r4, #0
    movne r0, r1
    mov r1, #0
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
    .size func_02020374, .-func_02020374
