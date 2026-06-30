extern void func_02021948(void);
extern void func_02021994(void);
extern void func_02021980(void);
extern void func_ov017_02080938(void);
extern void func_ov002_0207643c(void);

asm void func_ov017_02080cb4(void)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #0xc
    add     r4, r1, #0
    add     r1, #0x10
    add     r5, r0, #0
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
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r4, #8
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    add     r1, sp, #0
    bl      func_ov017_02080938
    add     r1, r0, #0
    add     r0, r6, #0
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #0xc
    pop     {r3, r4, r5, r6, pc}
}
