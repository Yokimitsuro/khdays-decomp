extern void func_02021980(void);
extern void func_02021994(void);
extern void func_02020400(void);
extern void func_ov002_02076468(void);
extern void func_ov017_020803c4(void);

asm void func_ov017_02080b08(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x34
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0x18]
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0x1c]
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0x20]
    add     r0, r5, #0
    add     r1, #0x28
    ldr     r7, [r4, #0x1c]
    ldr     r6, [r4, #0x24]
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0x24]
    add     r0, r5, #0
    add     r1, #0x30
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0x28]
    add     r0, r5, #0
    add     r1, #0x38
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0x2c]
    add     r0, r5, #0
    add     r1, #0x40
    bl      func_02021994
    add     r4, #0x48
    str     r0, [sp, #0x30]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    mov     r1, #0x5a
    lsl     r0, r0, #0x10
    lsl     r1, r1, #2
    bl      func_02020400
    lsl     r0, r0, #0x10
    lsr     r4, r0, #0x10
    ldr     r0, [sp, #0x18]
    bl      func_ov002_02076468
    lsr     r1, r7, #0x10
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    lsl     r1, r1, #0x18
    lsr     r1, r1, #0x18
    str     r1, [sp, #0]
    lsl     r1, r6, #0x10
    lsr     r1, r1, #0x10
    str     r1, [sp, #4]
    lsr     r1, r6, #0x10
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    lsl     r1, r1, #0x18
    lsr     r1, r1, #0x18
    str     r1, [sp, #8]
    ldr     r1, [sp, #0x24]
    ldr     r2, [sp, #0x20]
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    str     r1, [sp, #0xc]
    add     r1, sp, #0x28
    str     r1, [sp, #0x10]
    lsl     r1, r4, #0x10
    asr     r1, r1, #0x10
    str     r1, [sp, #0x14]
    ldr     r1, [sp, #0x1c]
    lsl     r2, r2, #0x10
    lsl     r1, r1, #0x10
    lsl     r3, r7, #0x10
    lsr     r1, r1, #0x10
    lsr     r2, r2, #0x10
    lsr     r3, r3, #0x10
    bl      func_ov017_020803c4
    mov     r0, #1
    add     sp, #0x34
    pop     {r4, r5, r6, r7, pc}
}
