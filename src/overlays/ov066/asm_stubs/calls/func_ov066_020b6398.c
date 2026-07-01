extern char data_ov066_020b6ae0[];

asm void func_ov066_020b6398(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r7, r0
    ldrb    r0, [r7, #0x19]
    mov     r6, r1
    mov     r4, #0
    cmp     r0, #0
    ldmlefd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r8, [pc, #0x3c]
    mov     r5, r4
_L0024:
    ldr     r0, [r7, #0xc]
    add     r1, r0, r5
    ldrsb   r0, [r1, #2]
    cmp     r0, #0
    beq     _L0048
    ldr     r3, [r8, r0, lsl #2]
    mov     r0, r7
    mov     r2, r6
    blx     r3
_L0048:
    ldrb    r0, [r7, #0x19]
    add     r4, r4, #1
    add     r5, r5, #0x1c8
    cmp     r4, r0
    blt     _L0024
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
    dcd     data_ov066_020b6ae0
}
