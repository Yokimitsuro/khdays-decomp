extern void func_ov002_0206e700(void);
extern void data_0204be18(void);

asm void func_ov069_020b847c(void)
{
    push    {r4, lr}
    ldr     r1, [pc, #0x24]
    add     r4, r0, #0
    ldr     r2, [r1, #0]
    ldr     r1, [pc, #0x20]
    mov     r0, #1
    ldrh    r1, [r2, r1]
    bl      func_ov002_0206e700
    ldr     r0, [pc, #0x14]
    ldr     r1, [r0, #0]
    ldr     r0, [pc, #0x14]
    ldrh    r0, [r1, r0]
    cmp     r0, r4
    blo     _L_0022
    mov     r0, #1
    pop     {r4, pc}
_L_0022:
    mov     r0, #0
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_0204be18
    add     r4, r5, r5
    lsl     r0, r0, #0
}
