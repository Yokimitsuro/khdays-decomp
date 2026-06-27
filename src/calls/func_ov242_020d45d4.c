extern int func_0203c634(void *r0, int r1, void *r2);
extern void func_ov242_020d4608(void *p);

asm void func_ov242_020d45d4(void *r0)
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
    ldr     r2, =func_ov242_020d4608
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
