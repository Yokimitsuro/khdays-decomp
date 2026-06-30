extern void func_02023588(void);

asm void func_ov069_020b82a4(void)
{
    push    {r3, r4, r5, lr}
    ldr     r2, [pc, #0x48]
    cmp     r0, r2
    beq     _L_0016
    add     r1, r2, #1
    cmp     r0, r1
    beq     _L_001e
    add     r1, r2, #2
    cmp     r0, r1
    beq     _L_0026
    b       _L_002c
_L_0016:
    ldr     r5, [pc, #0x38]
    add     r4, r5, #0
    add     r4, #0xb
    b       _L_0030
_L_001e:
    ldr     r5, [pc, #0x34]
    add     r4, r5, #0
    add     r4, #0x10
    b       _L_0030
_L_0026:
    ldr     r5, [pc, #0x30]
    add     r4, r5, #3
    b       _L_0030
_L_002c:
    mov     r0, #0
    pop     {r3, r4, r5, pc}
_L_0030:
    cmp     r5, r4
    bgt     _L_0048
_L_0034:
    add     r0, r5, #0
    bl      func_02023588
    cmp     r0, #0
    bne     _L_0042
    mov     r0, #0
    pop     {r3, r4, r5, pc}
_L_0042:
    add     r5, r5, #1
    cmp     r5, r4
    ble     _L_0034
_L_0048:
    mov     r0, #1
    pop     {r3, r4, r5, pc}
    lsl     r2, r3, #9
    lsl     r0, r0, #0
    asr     r4, r0, #0x11
    lsl     r0, r0, #0
    asr     r0, r2, #0x11
    lsl     r0, r0, #0
    asr     r1, r4, #0x11
    lsl     r0, r0, #0
}
