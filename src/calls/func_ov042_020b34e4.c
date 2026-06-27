extern void func_ov042_020b4358(void *r0, void *r1);
extern void func_ov022_020a384c(void *r0, int r1);

asm void func_ov042_020b34e4(void *r0, int r1)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r1
    mov     r5, r0
    cmp     r4, #0x2f
    add     r1, r5, #0x2c
    cmpne   r4, #0x30
    bne     _L_skip
    ldr     r0, [r5, #0x6bc]
    cmp     r4, r0
    beq     _L_skip
    mov     r0, r5
    add     r1, r1, #0x2c00
    bl      func_ov042_020b4358
_L_skip:
    mov     r0, r5
    mov     r1, r4
    bl      func_ov022_020a384c
    ldmfd   sp!, {r3, r4, r5, pc}
}
