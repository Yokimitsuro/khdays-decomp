extern int func_020235d0(int r0, int r1);

asm void *func_ov014_0207fcb0(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldrh    r0, [r4, #0x14]
    ldrb    r1, [r4, #0x16]
    bl      func_020235d0
    ldr     r1, =0xfffe
    and     r0, r0, r1
    mov     r0, r0, lsl #0xf
    mov     r0, r0, lsr #0x10
    tst     r0, #1
    moveq   r0, #0
    addne   r0, r4, #0x1c
    ldmfd   sp!, {r4, pc}
}
