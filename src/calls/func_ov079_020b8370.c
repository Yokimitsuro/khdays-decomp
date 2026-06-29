extern char data_ov079_020b9a00[];
extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);

asm void func_ov079_020b8370(void)
{
    push    {r4, lr}
    ldr     r0, [pc, #0x2c]
    mov     r1, #1
    ldr     r4, [r0, #0]
    mov     r2, #2
    add     r0, r4, #0
_L_000c:
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r4, #0
    add     r2, r1, #0
_L_0016:
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x18]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_002e
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_002e:
    pop     {r4, pc}
    dcd     data_ov079_020b9a00
    lsr     r5, r1, #0x1c
    lsl     r0, r0, #0
}
