extern int func_020235d0(int, int);
extern int func_020235e8(int, int, int);
extern int func_02023c40(void);

asm void func_ov019_0207fcdc(void)
{
    push    {r3, r4, r5, lr}
    ldr     r0, =0x20b7
    mov     r1, #8
    bl      func_020235d0
    add     r4, r0, #0
    mov     r0, #0x82
    lsl     r0, r0, #6
    mov     r1, #5
    bl      func_020235d0
    add     r5, r0, #0
    bl      func_02023c40
    cmp     r0, #1
    bne     _b1
    mov     r0, #3
    b       _a1
_b1:
    mov     r0, #2
_a1:
    add     r4, r4, r0
    cmp     r5, #1
    bne     _b2
    cmp     r4, #0x3b
    blt     _b3
    ldr     r0, =0x20b7
    mov     r1, #8
    mov     r2, #0
    bl      func_020235e8
    mov     r0, #1
    pop     {r3, r4, r5, pc}
_b2:
    cmp     r4, #0x77
    blt     _b3
    ldr     r0, =0x20b7
    mov     r1, #8
    mov     r2, #0
    bl      func_020235e8
    mov     r0, #1
    pop     {r3, r4, r5, pc}
_b3:
    lsl     r2, r4, #0x10
    ldr     r0, =0x20b7
    mov     r1, #8
    lsr     r2, r2, #0x10
    bl      func_020235e8
    mov     r0, #0
    pop     {r3, r4, r5, pc}
}
