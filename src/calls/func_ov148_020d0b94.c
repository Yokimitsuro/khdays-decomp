extern int func_0203c634(void *r0, int r1, void *r2);
extern void func_ov148_020d0bfc(void *p);

asm void func_ov148_020d0b94(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     lr, [r0, #4]
    ldr     r2, =func_ov148_020d0bfc
    ldr     ip, [lr]
    ldrh    r3, [ip, #0x60]
    mov     r1, r3, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x86
    bic     r3, r3, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r3, r1, lsr #0x10
    strh    r1, [ip, #0x60]
    ldr     r1, [lr]
    ldr     ip, [r1, #0x38c]
    ldr     r3, [ip, #8]
    mov     r1, r3, lsl #0x18
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #1
    bic     r3, r3, #0xff
    and     r1, r1, #0xff
    orr     r1, r3, r1
    str     r1, [ip, #8]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
