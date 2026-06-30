extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_ov022_020911f0(void);
extern void func_020358f4(void);
extern void func_ov022_02091254(void);
extern void data_ov036_020b4f18(void);

asm void func_ov036_020b4b9c(void)
{
    push    {r4, lr}
    sub     sp, #0x50
    add     r4, r0, #0
    mov     r0, #0x90
    bl      NNSi_FndAllocFromDefaultExpHeap
    ldr     r1, [pc, #0x78]
    mov     r2, #1
    str     r0, [r4, r1]
    ldr     r0, [r4, r1]
    mov     r1, #0
    bl      func_ov022_020911f0
    mov     r3, #5
    mov     r1, #0
    ldr     r0, [pc, #0x6c]
    str     r3, [sp, #0]
    str     r1, [sp, #4]
    add     r2, sp, #0
    strh    r0, [r2, #0xa]
    lsl     r2, r3, #9
    str     r2, [sp, #0xc]
    mov     r2, #0x32
    lsl     r2, r2, #6
    str     r2, [sp, #0x10]
    lsl     r2, r3, #0xd
    str     r2, [sp, #0x14]
    mov     r2, #0x1e
    lsl     r2, r2, #0xc
    str     r2, [sp, #0x18]
    add     r2, r0, #0
    sub     r0, #0x9a
    sub     r2, #0x7a
    str     r2, [sp, #0x24]
    ldr     r2, [pc, #0x48]
    str     r1, [sp, #0x1c]
    str     r1, [sp, #0x28]
    mov     r1, #3
    lsl     r1, r1, #8
    str     r1, [sp, #0x30]
    str     r0, [sp, #0x2c]
    str     r0, [sp, #0x34]
    mov     r0, #4
    str     r0, [sp, #0x38]
    str     r2, [sp, #0x20]
    mov     r1, #8
    add     r0, sp, #0x40
    strb    r1, [r0, #0xc]
    ldrb    r0, [r4, #9]
    mov     r1, #0x30
    bl      func_020358f4
    cmp     r0, #0
    beq     _L_0074
    ldr     r1, [sp, #0]
    mov     r0, #1
    orr     r0, r1
    str     r0, [sp, #0]
_L_0074:
    ldr     r0, [pc, #0x10]
    ldr     r2, [pc, #0x1c]
    ldr     r0, [r4, r0]
    add     r1, r4, #0
    add     r3, sp, #0
    bl      func_ov022_02091254
    add     sp, #0x50
    pop     {r4, pc}
    mov     r8, r8
    mov     r6, #0x44
    lsl     r0, r0, #0
    lsl     r2, r3, #6
    lsl     r0, r0, #0
    dcd     0x7fffffff
    dcd     data_ov036_020b4f18
}
