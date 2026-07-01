extern void func_02021980(void);
extern void func_020235d0(void);
extern void func_020235e8(void);
extern void func_020235a8(void);
extern void data_0204be18(void);

asm void func_ov069_020b8548(void)
{
    push    {r4, r5, r6, lr}
    add     r5, r1, #0
    add     r6, r0, #0
    bl      func_02021980
    add     r5, #8
    add     r4, r0, #0
    add     r0, r6, #0
    add     r1, r5, #0
    bl      func_02021980
    mov     r1, #0
    mvn     r1, r1
    cmp     r4, r1
    bne     _L_0078
    cmp     r0, #0xc
    bne     _L_0058
    ldr     r0, [pc, #0x80]
    mov     r1, #2
    bl      func_020235d0
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    cmp     r0, #1
    bhs     _L_003c
    ldr     r0, [pc, #0x70]
    mov     r1, #2
    mov     r2, #1
    bl      func_020235e8
_L_003c:
    ldr     r0, [pc, #0x68]
    mov     r1, #2
    bl      func_020235d0
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    cmp     r0, #1
    bhs     _L_00a0
    ldr     r0, [pc, #0x58]
    mov     r1, #2
    mov     r2, #1
    bl      func_020235e8
    b       _L_00a0
_L_0058:
    ldr     r5, [pc, #0x50]
    lsl     r4, r0, #1
    add     r0, r4, r5
    mov     r1, #2
    bl      func_020235d0
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    cmp     r0, #1
    bhs     _L_00a0
    add     r0, r4, r5
    mov     r1, #2
    mov     r2, #1
    bl      func_020235e8
    b       _L_00a0
_L_0078:
    cmp     r4, #0
    ble     _L_00a0
    ldr     r1, [pc, #0x30]
    cmp     r4, r1
    bge     _L_00a0
    ldr     r1, [pc, #0x30]
    ldr     r2, [r1, #0]
    mov     r1, #0x81
    lsl     r1, r1, #4
    add     r2, r2, r1
    ldrb    r1, [r2, r4]
    add     r0, r1, r0
    cmp     r0, #0x63
    ble     _L_0096
    mov     r0, #0x63
_L_0096:
    strb    r0, [r2, r4]
    ldr     r0, [pc, #0x1c]
    add     r0, r4, r0
    bl      func_020235a8
_L_00a0:
    mov     r0, #1
    pop     {r4, r5, r6, pc}
    add     r7, #0xb7
    lsl     r0, r0, #0
    add     r7, #0xb9
    lsl     r0, r0, #0
    add     r7, #0x9f
    lsl     r0, r0, #0
    lsl     r7, r6, #9
    lsl     r0, r0, #0
    dcd     data_0204be18
    lsl     r3, r3, #0x13
    lsl     r0, r0, #0
}
