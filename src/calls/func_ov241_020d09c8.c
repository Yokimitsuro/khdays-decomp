extern int func_02020400(int);
extern void func_0203c634(void *r0, int r1, int r2);

asm void func_ov241_020d09c8(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    ldr     r1, [r4]
    ldr     r0, [r1, #0x3a4]
    cmp     r0, #0
    ldrne   r1, [r1, #0x3a8]
    cmpne   r1, #0
    beq     _skip
    ldr     r0, [r4, #0x24]
    add     r0, r0, #1
    bl      func_02020400
    str     r1, [r4, #0x24]
    ldr     r0, [r4]
    ldr     r2, [r0, #0x3a4]
    mov     r0, #0x14
    mla     r0, r1, r0, r2
    str     r0, [r4, #0x1c]
_skip:
    ldr     r0, [r4]
    mov     r1, #3
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
