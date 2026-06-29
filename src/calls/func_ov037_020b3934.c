extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_020358f4(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091254(void);

asm void func_ov037_020b3934(void)
{
    push    {r4, r5, r6, lr}
    sub     sp, #0x50
    add     r5, r0, #0
    mov     r0, #0x30
    ldr     r4, [pc, #0x90]
_L_000a:
    bl      NNSi_FndAllocFromDefaultExpHeap
    ldr     r1, [pc, #0x90]
    mov     r2, #1
    str     r0, [r5, r1]
    ldr     r0, [r5, r1]
    mov     r1, #0
_L_0018:
    bl      func_ov022_020911f0
    mov     r3, #1
    mov     r2, #0
    str     r3, [sp, #0]
    ldr     r1, [pc, #0x80]
    str     r2, [sp, #4]
    add     r0, sp, #0
    strh    r1, [r0, #0xa]
    sub     r1, #0x9a
    lsl     r3, r3, #0xc
    str     r3, [sp, #0x10]
    mov     r3, #0xa
    ldr     r0, [pc, #0x74]
    lsl     r3, r3, #0xc
    str     r3, [sp, #0x14]
    lsl     r3, r3, #1
    str     r0, [sp, #0xc]
    str     r3, [sp, #0x18]
    ldr     r3, [pc, #0x6c]
    sub     r0, #0x33
    str     r0, [sp, #0x30]
    mov     r0, #4
    str     r0, [sp, #0x38]
    str     r2, [sp, #0x1c]
    str     r3, [sp, #0x20]
    str     r2, [sp, #0x28]
    str     r1, [sp, #0x2c]
    str     r1, [sp, #0x34]
    mov     r1, #8
    add     r0, sp, #0x40
    strb    r1, [r0, #0xc]
    ldrb    r0, [r5, #9]
    mov     r1, #0x30
_L_005c:
    bl      func_020358f4
    cmp     r0, #0
    beq     _L_006c
    ldr     r1, [sp, #0]
    mov     r0, #1
    orr     r0, r1
    str     r0, [sp, #0]
_L_006c:
    ldr     r2, [pc, #0x40]
    mov     r6, #2
    ldr     r2, [r5, r2]
    lsl     r6, r6, #0xe
    add     r3, r2, r6
    ldr     r2, [pc, #0x3c]
    ldrb    r4, [r5, r4]
    and     r3, r2
    ldr     r0, [pc, #0x20]
    lsl     r3, r3, #7
    lsl     r6, r6, #0x10
    add     r4, #0xbe
    lsr     r2, r2, #0xf
    ldr     r0, [r5, r0]
    orr     r3, r6
    and     r2, r4
    orr     r2, r3
    add     r1, r5, #0
    add     r3, sp, #0
_L_0092:
    bl      func_ov022_02091254
    add     sp, #0x50
    pop     {r4, r5, r6, pc}
    mov     r8, r8
    lsr     r0, r3, #4
    lsl     r0, r0, #0
    mov     r6, #0x44
    lsl     r0, r0, #0
    lsl     r2, r3, #6
    lsl     r0, r0, #0
    lsl     r3, r6, #0xc
    lsl     r0, r0, #0
    dcd     0x7fffffff
    dcd     0x00002bd0
    dcd     0x00fffffc
}
