extern void func_ov022_02091eb0(void *r0);

asm void func_ov042_020b41a0(void *r0)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    ldrb    r0, [r6, #0x19]
    mov     r4, #0
    cmp     r0, #0
    ldmlefd sp!, {r4, r5, r6, pc}
    mov     r5, r4
_L_loop:
    ldr     r0, [r6, #0xc]
    add     r0, r0, r5
    ldrsb   r1, [r0, #2]
    cmp     r1, #0
    cmpne   r1, #2
    cmpne   r1, #3
    beq     _L_skip
    bl      func_ov022_02091eb0
_L_skip:
    ldrb    r0, [r6, #0x19]
    add     r4, r4, #1
    add     r5, r5, #0x1c8
    cmp     r4, r0
    blt     _L_loop
    ldmfd   sp!, {r4, r5, r6, pc}
}
