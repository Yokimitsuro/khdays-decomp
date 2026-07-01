extern void func_ov031_020b3c60(void);

asm void func_ov031_020b3dbc(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    ldrb    r0, [r6, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldmeqfd sp!, {r4, r5, r6, pc}
    add     r5, r1, #0xc
    mov     r4, #0
_loop:
    mov     r0, r6
    mov     r1, r5
    mov     r2, r4
    bl      func_ov031_020b3c60
    add     r4, r4, #1
    cmp     r4, #2
    add     r5, r5, #0x118
    blt     _loop
    ldmfd   sp!, {r4, r5, r6, pc}
}
