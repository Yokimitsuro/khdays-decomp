extern char data_ov044_020b55c4[];
extern void func_0202a634(void);

asm void func_ov044_020b3ad0(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r1, [pc, #0x30]
    mov     r4, #0
    ldr     r6, [r0, r1]
    mov     r1, #0x8d
    lsl     r1, r1, #2
    add     r5, r0, r1
    add     r7, r4, #0
_L_0010:
    ldrb    r3, [r6, #9]
    ldr     r1, [pc, #0x24]
    add     r0, r5, #0
    mov     r2, #1
    add     r3, r3, #7
_L_001a:
    bl      func_0202a634
    ldr     r0, [pc, #0x1c]
    strb    r4, [r5, r0]
    sub     r0, r0, #1
    strb    r7, [r5, r0]
    mov     r0, #0x17
    lsl     r0, r0, #4
    add     r4, r4, #1
    add     r5, r5, r0
    cmp     r4, #8
    blt     _L_0010
    pop     {r3, r4, r5, r6, r7, pc}
    lsr     r4, r6, #0x16
    lsl     r0, r0, #0
    dcd     data_ov044_020b55c4
    dcd     0x0000012d
}
