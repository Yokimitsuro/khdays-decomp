extern void func_02025694(void);
extern void data_0204be18(void);

asm void func_ov069_020b812c(void)
{
    push    {r3, lr}
    add     r1, r0, #0
    mov     r0, #1
    lsl     r0, r0, #0xa
    cmp     r1, r0
    blo     _L_0010
    mov     r0, #0
    pop     {r3, pc}
_L_0010:
    ldr     r0, [pc, #0x14]
    ldr     r2, [r0, #0]
    ldr     r0, [pc, #0x14]
    add     r0, r2, r0
    bl      func_02025694
    cmp     r0, #0
    beq     _L_0024
    mov     r0, #1
    pop     {r3, pc}
_L_0024:
    mov     r0, #0
    pop     {r3, pc}
    dcd     data_0204be18
    asr     r0, r4, #3
    lsl     r0, r0, #0
}
