extern int func_02021980(void);
extern int func_020235d0(int, int);
extern int func_020235e8(int, int, int);
extern int func_ov002_02078f60(void);

asm void func_ov019_0207fa40(void)
{
    push    {r3, r4, r5, lr}
    bl      func_02021980
    add     r4, r0, #0
    ldr     r0, =0x208f
    mov     r1, #0xa
    bl      func_020235d0
    add     r5, r0, #0
    cmp     r4, #0
    bne     _n0
    ldr     r4, =0x140b
    b       _do
_n0:
    cmp     r4, #1
    bne     _n1
    ldr     r4, =0x1415
    b       _do
_n1:
    ldr     r4, =0x141f
_do:
    add     r0, r4, #0
    mov     r1, #0xa
    bl      func_020235d0
    cmp     r5, r0
    ble     _end
    lsl     r2, r5, #0x10
    add     r0, r4, #0
    mov     r1, #0xa
    lsr     r2, r2, #0x10
    bl      func_020235e8
_end:
    bl      func_ov002_02078f60
    mov     r0, #1
    pop     {r3, r4, r5, pc}
}
