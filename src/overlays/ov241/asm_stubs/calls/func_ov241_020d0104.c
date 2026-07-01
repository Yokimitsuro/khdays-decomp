extern void func_0203d194(void *);
extern void *func_0203d15c(int);
extern void MI_CpuCopy8(void *, void *, int);

asm void func_ov241_020d0104(void *r0, int r1, void *r2)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r0, [r5, #0x3a4]
    mov     r4, r2
    cmp     r0, #0
    beq     _skip
    bl      func_0203d194
    mov     r0, #0
    str     r0, [r5, #0x3a4]
_skip:
    ldr     r1, [r4, #8]
    mov     r0, #0x14
    mul     r0, r1, r0
    bl      func_0203d15c
    str     r0, [r5, #0x3a4]
    ldr     r1, [r4, #8]
    mov     r0, #0x14
    mul     r2, r1, r0
    ldr     r1, [r5, #0x3a4]
    add     r0, r4, #0xc
    bl      MI_CpuCopy8
    ldr     r0, [r4, #8]
    str     r0, [r5, #0x3a8]
    ldr     r0, [r4]
    str     r0, [r5, #0x3b4]
    ldr     r0, [r4, #4]
    str     r0, [r5, #0x3b8]
    ldmfd   sp!, {r3, r4, r5, pc}
}
