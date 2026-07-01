extern void func_02021948(void);
extern void func_02021980(void);
extern void func_02021994(void);
extern void func_ov002_0207643c(void);
extern void func_ov014_02080540(void);

asm void func_ov014_020807c4(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0xc
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    add     r7, r0, #0
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    lsl     r0, r0, #0x10
    lsr     r6, r0, #0x10
    mov     r0, #0x10
    ldrsh   r0, [r4, r0]
    cmp     r0, #0
    bne     _L_0028
    mov     r0, #0
    b       _L_0032
_L_0028:
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021948
_L_0032:
    add     r1, r4, #0
    str     r0, [sp, #0]
    add     r0, r5, #0
    add     r1, #0x18
    bl      func_02021994
    add     r4, #0x20
    str     r0, [sp, #4]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021994
    str     r0, [sp, #8]
    add     r0, r6, #0
    add     r1, sp, #0
    bl      func_ov014_02080540
    add     r1, r0, #0
    add     r0, r7, #0
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #0xc
    pop     {r4, r5, r6, r7, pc}
}
