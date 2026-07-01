extern void func_02014dc4(void *arg);
extern void *data_ov034_020b5570;

asm void func_ov034_020b3c04(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub     sp, sp, #0xc
    ldr     r1, =data_ov034_020b5570
    add     r5, sp, #0
    add     r6, r0, #0xf10
    ldmia   r1, {r0, r1, r2}
    mov     r7, #0
    stmia   r5, {r0, r1, r2}
    mov     r4, r7
    mvn     r9, #0
_loop:
    ldr     r8, [r5, r7, lsl #2]
    add     r0, r6, r8, lsl #2
    ldr     r1, [r0, #0xc]
    cmp     r1, #0
    beq     _skip
    add     r0, r6, #0x20
    bl      func_02014dc4
    add     r0, r6, r8, lsl #2
    str     r4, [r0, #0xc]
_skip:
    add     r0, r6, r8, lsl #1
    add     r7, r7, #1
    strh    r9, [r0, #2]
    cmp     r7, #3
    blt     _loop
    add     sp, sp, #0xc
    ldmfd   sp!, {r4, r5, r6, r7, r8, r9, pc}
}
