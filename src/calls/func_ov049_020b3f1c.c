extern void func_ov049_020b406c(void);
extern void *data_ov049_020b4d00;

asm void func_ov049_020b3f1c(void)
{
    stmfd   sp!, {r4, lr}
    ldr     r2, =data_ov049_020b4d00
    add     r1, r0, #0x2000
    ldr     r3, [r2]
    ldr     r2, [r1, #0x640]
    add     r1, r3, #0xfc
    add     r4, r1, #0x2c00
    add     r1, r2, #4
    str     r1, [r4, #0x10c]
    bl      func_ov049_020b406c
    mov     r0, #0
    str     r0, [r4, #0x120]
    ldmfd   sp!, {r4, pc}
}
