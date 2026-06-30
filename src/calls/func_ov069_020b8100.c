extern void func_020235a8(void);
extern void func_020235bc(void);
extern void data_ov069_020baa2c(void);

asm void func_ov069_020b8100(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    ldr     r0, [pc, #0x20]
    lsl     r1, r1, #2
    ldr     r1, [r0, r1]
    cmp     r1, #0
    beq     _L_0024
    add     r0, r2, #0
    blx     r1
    cmp     r0, #0
    beq     _L_001e
    add     r0, r4, #0
    bl      func_020235a8
    pop     {r4, pc}
_L_001e:
    add     r0, r4, #0
    bl      func_020235bc
_L_0024:
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_ov069_020baa2c
}
