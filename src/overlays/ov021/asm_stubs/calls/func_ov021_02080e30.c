extern void func_02021948(void);
extern void func_02021980(void);
extern void func_ov002_0207643c(void);
extern void func_ov021_02080b44(void);

asm void func_ov021_02080e30(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #8
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
    add     r4, #0x18
    str     r0, [sp, #0]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021948
    str     r0, [sp, #4]
    lsl     r0, r6, #0x10
    lsr     r0, r0, #0x10
    add     r1, sp, #0
    bl      func_ov021_02080b44
    add     r1, r0, #0
    add     r0, r7, #0
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #8
    pop     {r3, r4, r5, r6, r7, pc}
}
