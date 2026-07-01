extern void func_02021948(void);
extern void func_02021980(void);
extern void func_02021994(void);
extern void func_ov002_0207643c(void);
extern void func_ov014_0207ffdc(void);

asm void func_ov014_02080664(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0x20
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
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #4]
    add     r0, r5, #0
    add     r1, #0x20
    bl      func_02021980
    add     r1, sp, #0
    strb    r0, [r1, #8]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x28
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0xa]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x30
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0xc]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x38
    bl      func_02021994
    add     r1, sp, #0
    strh    r0, [r1, #0xe]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x40
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0x10]
    add     r0, r5, #0
    add     r1, #0x48
    bl      func_02021980
    add     r1, sp, #0
    strb    r0, [r1, #0x1c]
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x50
    bl      func_02021994
    add     r4, #0x58
    str     r0, [sp, #0x14]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021994
    str     r0, [sp, #0x18]
    lsl     r0, r6, #0x10
    lsr     r0, r0, #0x10
    add     r1, sp, #0
    bl      func_ov014_0207ffdc
    add     r1, r0, #0
    add     r0, r7, #0
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #0x20
    pop     {r3, r4, r5, r6, r7, pc}
}
