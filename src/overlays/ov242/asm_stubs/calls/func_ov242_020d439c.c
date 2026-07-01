extern void func_0203c634(void);
extern void func_ov242_020d4404(void);

asm void func_ov242_020d439c(void)
{
    stmfd   sp!, {r3, lr}
    ldr     r1, [r0, #4]
    mov     r2, #0
    ldr     lr, [r1]
    ldrh    ip, [lr, #0x60]
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    orr     r3, r3, #0x86
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #16
    strh    r3, [lr, #0x60]
_L_0030:
    ldr     r3, [r1]
    add     r3, r3, r2, lsl #2
    ldr     ip, [r3, #0x38c]
    add     r2, r2, #1
    ldr     r3, [ip, #0x5c]
    cmp     r2, #3
    orr     r3, r3, #2
    str     r3, [ip, #0x5c]
    blt     _L_0030
    ldrsb   r1, [r0, #0x20]
    ldr     r2, =func_ov242_020d4404
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
