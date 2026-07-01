extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov241_020d0940(void);

asm void func_ov241_020d08ec(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldmia   r4, {r0, r2}
    ldr     r1, [r2, #0x2c]
    ldr     r0, [r0, #0x2c]
    sub     r0, r1, r0
    str     r0, [r2, #0x2c]
    ldr     r0, [r2]
    ldr     r1, [r0, #0x384]
    ldrb    r1, [r1, #0xad]
    cmp     r1, #0
    ldmnefd sp!, {r4, pc}
    mov     r1, #6
    mov     r2, #0
    bl      func_ov107_020c9264
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov241_020d0940
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
