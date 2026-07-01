extern void func_0203c634(void);
extern void func_ov241_020d09c8(void);

asm void func_ov241_020d0994(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldmia   r0, {r1, r3}
    ldr     r2, [r3, #0x2c]
    ldr     r1, [r1, #0x2c]
    sub     r1, r2, r1
    str     r1, [r3, #0x2c]
    cmp     r1, #0
    ldmgtfd sp!, {r3, pc}
    ldrsb   r1, [r0, #0x20]
    ldr     r2, =func_ov241_020d09c8
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
