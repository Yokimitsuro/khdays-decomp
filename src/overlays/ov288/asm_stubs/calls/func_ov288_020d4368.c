extern int func_02023eb4(int r0);
extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern void func_0203c634(void *r0, int r1, int r2);

asm void func_ov288_020d4368(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    ldr     r5, [r4, #4]
    ldr     r0, [r5]
    ldrh    r0, [r0, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    ldmeqfd sp!, {r3, r4, r5, pc}
    mov     r0, #0x64
    bl      func_02023eb4
    cmp     r0, #0xa
    movlo   r2, #1
    ldr     r0, [r5]
    movhs   r2, #0
    str     r2, [r0, #0x38c]
    ldr     r0, [r5]
    mov     r1, #1
    mov     r2, #0
    bl      func_ov107_020c9264
    ldr     r3, [r5]
    mov     r0, r4
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc9]
    mov     r2, #0
    strb    r1, [r3, #0x1c7]
    ldrsb   r1, [r4, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
