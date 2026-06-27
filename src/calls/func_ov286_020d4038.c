extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov286_020d409c(void);

asm void func_ov286_020d4038(void *arg)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    ldr     r1, [r4]
    mov     r0, #0x1e
    ldr     r1, [r1, #0x2c]
    ldr     r2, =0x66666667
    mul     r3, r1, r0
    mov     r0, r3, lsr #0x1f
    smull   r1, r3, r2, r3
    ldr     r5, [r4, #4]
    add     r3, r0, r3, asr #1
    str     r3, [r5, #0x14]
    ldr     r0, [r5]
    mov     r1, #0
    mov     r2, #1
    bl      func_ov107_020c9264
    mov     r0, #0
    str     r0, [r5, #0x28]
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov286_020d409c
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
