extern void *NNSi_FndAllocFromDefaultExpHeap(int);
extern void MI_CpuFill8(void *, int, int);
extern int func_ov302_020cbf20(int *a, void *b);

asm void func_ov302_020cbf64(void *r0, void *r1)
{
    stmfd   sp!, {r3, r4, r5, r6, lr}
    sub     sp, sp, #4
    mov     r6, r0
    mov     r0, #0x58
    mov     r5, r1
    bl      NNSi_FndAllocFromDefaultExpHeap
    mov     r1, #0
    mov     r2, #0x58
    mov     r4, r0
    bl      MI_CpuFill8
    ldrh    r0, [r6, #2]
    mov     r1, r5
    strh    r0, [r4]
    ldrh    r0, [r6, #4]
    strh    r0, [r4, #2]
    ldrh    r0, [r6, #0xa]
    strh    r0, [r4, #4]
    ldrh    r0, [r6, #0xe]
    strh    r0, [r4, #6]
    ldrh    r0, [r6, #0x10]
    strh    r0, [r4, #8]
    ldrh    r0, [r6, #0x12]
    strh    r0, [r4, #0xa]
    ldrb    r0, [r6, #0x14]
    strb    r0, [r4, #0xc]
    ldrh    r0, [r6, #0xc]
    cmp     r0, #1
    moveq   r0, #1
    movne   r0, #0
    str     r0, [r4, #0x10]
    ldrb    r2, [r6, #0x16]
    add     r0, sp, #0
    strb    r2, [r4, #0x14]
    ldrb    r2, [r6, #0x15]
    strb    r2, [r4, #0xd]
    ldrb    r2, [r6, #0x17]
    strb    r2, [r4, #0x15]
    ldrh    r2, [r6, #6]
    str     r2, [r4, #0x1c]
    ldrb    r2, [r6, #0x23]
    str     r2, [r4, #0x18]
    ldrh    r2, [r6, #0x18]
    strh    r2, [r4, #0x20]
    ldrh    r2, [r6, #0x1a]
    strh    r2, [r4, #0x22]
    ldrh    r2, [r6, #0x1c]
    strh    r2, [r4, #0x24]
    ldrh    r2, [r6, #0x1e]
    strb    r2, [r4, #0x26]
    ldrh    r2, [r6, #0x20]
    strb    r2, [r4, #0x27]
    ldrb    r2, [r6, #0x22]
    strb    r2, [r4, #0x28]
    ldrh    r2, [r6, #0x24]
    strh    r2, [r4, #0x2a]
    ldrh    r2, [r6, #0x26]
    strh    r2, [r4, #0x2c]
    ldrh    r2, [r6, #0x28]
    strh    r2, [r4, #0x2e]
    ldrh    r2, [r6, #0x2a]
    str     r2, [r4, #0x30]
    ldrh    r2, [r6, #0x2c]
    str     r2, [r4, #0x34]
    ldrh    r2, [r6, #0x2e]
    str     r2, [r4, #0x38]
    bl      func_ov302_020cbf20
    str     r0, [r4, #0x3c]
    ldr     r1, [sp]
    add     r0, sp, #0
    bl      func_ov302_020cbf20
    str     r0, [r4, #0x40]
    ldr     r1, [sp]
    add     r0, sp, #0
    bl      func_ov302_020cbf20
    str     r0, [r4, #0x44]
    ldr     r1, [sp]
    mov     r0, #0
    bl      func_ov302_020cbf20
    str     r0, [r4, #0x48]
    mov     r0, r4
    add     sp, sp, #4
    ldmfd   sp!, {r3, r4, r5, r6, pc}
}
