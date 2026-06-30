extern void func_02021980(void);
extern void func_02021948(void);
extern void func_02021994(void);
extern void func_ov017_020802d8(void);
extern void func_ov002_0207643c(void);

asm void func_ov017_02080a6c(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0x18
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    add     r7, r0, #0
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021948
    add     r1, r4, #0
    str     r0, [sp, #0]
    add     r0, r5, #0
    add     r1, #0x18
    bl      func_02021948
    add     r1, r4, #0
    str     r0, [sp, #4]
    add     r0, r5, #0
    add     r1, #0x20
    bl      func_02021948
    add     r1, r4, #0
    str     r0, [sp, #8]
    add     r0, r5, #0
    add     r1, #0x28
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0xc]
    add     r0, r5, #0
    add     r1, #0x30
    bl      func_02021980
    add     r1, sp, #0
    strb    r0, [r1, #0x10]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x38
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0x12]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x40
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0x14]
    add     r4, #0x48
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0x16]
    lsl     r0, r6, #0x10
    lsr     r0, r0, #0x10
    add     r1, sp, #0
    bl      func_ov017_020802d8
    add     r1, r0, #0
    add     r0, r7, #0
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #0x18
    pop     {r3, r4, r5, r6, r7, pc}
}
