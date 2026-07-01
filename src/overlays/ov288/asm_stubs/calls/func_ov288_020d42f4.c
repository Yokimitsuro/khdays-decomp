extern void func_0203c634(void *r0, int r1, void *r2);
extern void func_ov288_020d4368(void);

asm void func_ov288_020d42f4(void *r0)
{
    stmfd   sp!, {r4, lr}
    ldr     r1, [r0, #4]
    mov     r3, #0
    ldr     lr, [r1]
    ldr     r2, =func_ov288_020d4368
    ldrh    ip, [lr, #0x60]
    mov     r4, ip, lsl #0x10
    mov     r4, r4, lsr #0x18
    orr     r4, r4, #0x80
    bic     ip, ip, #0xff00
    mov     r4, r4, lsl #0x18
    orr     r4, ip, r4, lsr #0x10
    strh    r4, [lr, #0x60]
    ldr     r4, [r1]
    ldr     r4, [r4, #0x388]
    ldr     lr, [r4, #8]
    mov     ip, lr, lsl #0x18
    mov     ip, ip, lsr #0x18
    bic     ip, ip, #1
    bic     lr, lr, #0xff
    and     ip, ip, #0xff
    orr     ip, lr, ip
    str     ip, [r4, #8]
    ldr     r1, [r1]
    str     r3, [r1, #0x394]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
