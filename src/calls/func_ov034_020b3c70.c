extern void func_ov034_020b531c(void);
extern void func_ov034_020b5490(void);
extern void *data_ov034_020b5660;

asm void func_ov034_020b3c70(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r2, =data_ov034_020b5660
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldr     r3, [r2]
    ldrsh   r2, [r1, #0xba]
    add     r4, r3, #0xe4
    add     r1, r4, #0x2c00
    bl      func_ov034_020b531c
    mov     r0, r5
    add     r1, r4, #0x2c00
    bl      func_ov034_020b5490
    ldmfd   sp!, {r3, r4, r5, pc}
}
