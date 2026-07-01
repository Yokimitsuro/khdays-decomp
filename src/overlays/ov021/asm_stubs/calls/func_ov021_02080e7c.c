extern void func_02020400(void);
extern void func_02021980(void);
extern void func_02021994(void);
extern void func_ov002_02076468(void);
extern void func_ov021_02080bd0(void);

asm void func_ov021_02080e7c(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0x20
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0xc]
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    add     r7, r0, #0
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0x10]
    ldr     r6, [r4, #0x1c]
    add     r0, r5, #0
    add     r1, #0x20
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0x14]
    add     r0, r5, #0
    add     r1, #0x28
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0x18]
    add     r0, r5, #0
    add     r1, #0x30
    bl      func_02021994
    add     r4, #0x38
    str     r0, [sp, #0x1c]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r4, r0, #0
    ldr     r0, [sp, #0xc]
    bl      func_ov002_02076468
    mov     r1, #0x5a
    add     r5, r0, #0
    lsl     r0, r4, #0x10
    lsl     r1, r1, #2
    bl      func_02020400
    lsl     r0, r0, #0x10
    asr     r0, r0, #0x10
    str     r0, [sp, #0]
    lsl     r0, r6, #0x10
    lsr     r0, r0, #0x10
    str     r0, [sp, #4]
    lsr     r0, r6, #0x10
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    ldr     r2, [sp, #0x10]
    lsl     r0, r0, #0x18
    lsr     r0, r0, #0x18
    lsl     r1, r7, #0x10
    lsl     r2, r2, #0x10
    str     r0, [sp, #8]
    add     r0, r5, #0
    lsr     r1, r1, #0x10
    lsr     r2, r2, #0x10
    add     r3, sp, #0x14
    bl      func_ov021_02080bd0
    mov     r0, #1
    add     sp, #0x20
    pop     {r3, r4, r5, r6, r7, pc}
}
