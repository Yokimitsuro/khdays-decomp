extern void func_02021980(void);
extern void func_ov069_020b8100(void);

asm void func_ov069_020b8518(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    add     r5, r1, #0
    ldr     r1, [r5, #4]
    add     r6, r0, #0
    lsl     r1, r1, #0x10
    lsr     r4, r1, #0x10
    add     r1, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r5, #0x10
    add     r7, r0, #0
    add     r0, r6, #0
    add     r1, r5, #0
    bl      func_02021980
    add     r2, r0, #0
    add     r0, r4, #0
    add     r1, r7, #0
    bl      func_ov069_020b8100
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
}
