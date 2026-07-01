extern void func_ov107_020c9264(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov241_020d0c5c(void);

asm void func_ov241_020d0c08(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #4
    ldr     r0, [r4]
    mov     r2, #0
    bl      func_ov107_020c9264
    ldr     r0, [r4]
    ldr     r3, [r4, #0xc]
    ldr     r1, =0x13a
    mov     r2, #5
    bl      func_ov107_020c5af8
    mov     r0, #0
    strb    r0, [r4, #0x40]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov241_020d0c5c
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
