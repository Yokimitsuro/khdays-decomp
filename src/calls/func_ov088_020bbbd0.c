extern void *data_ov088_020bc288;

asm void func_ov088_020bbbd0(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r7, r0
    ldrb    r0, [r7, #0x19]
    mov     r6, r1
    mov     r4, #0
    cmp     r0, #0
    ldmlefd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r8, =data_ov088_020bc288
    mov     r5, r4
_loop:
    ldr     r0, [r7, #0xc]
    add     r1, r0, r5
    ldrsb   r0, [r1, #2]
    cmp     r0, #0
    beq     _skip
    ldr     r3, [r8, r0, lsl #2]
    mov     r0, r7
    mov     r2, r6
    blx     r3
_skip:
    ldrb    r0, [r7, #0x19]
    add     r4, r4, #1
    add     r5, r5, #0x1c8
    cmp     r4, r0
    blt     _loop
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
