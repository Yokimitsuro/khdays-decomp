extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov286_020d3f18(void);

asm void func_ov286_020d3e50(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r3, [r4, #4]
    mov     r1, #0
    ldr     lr, [r3]
    mov     r2, #0x48
    ldrh    ip, [lr, #0x60]
    mov     r0, ip, lsl #0x10
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #0xc0
    bic     ip, ip, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, ip, r0, lsr #16
    strh    r0, [lr, #0x60]
    ldr     r0, [r3]
    ldrh    lr, [r0, #0x60]
    mov     ip, lr, lsl #0x10
    mov     ip, ip, lsr #0x18
    bic     ip, ip, #2
    mov     ip, ip, lsl #0x10
    mov     ip, ip, lsr #0x10
    bic     lr, lr, #0xff00
    mov     ip, ip, lsl #0x18
    orr     ip, lr, ip, lsr #16
    strh    ip, [r0, #0x60]
    ldr     r0, [r3]
    add     r0, r0, #0x100
    ldrh    ip, [r0, #0xae]
    orr     ip, ip, #1
    strh    ip, [r0, #0xae]
    ldr     r0, [r3]
    ldr     lr, [r0, #0x38c]
    ldr     ip, [lr, #8]
    mov     r0, ip, lsl #0x18
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #1
    bic     ip, ip, #0xff
    and     r0, r0, #0xff
    orr     r0, ip, r0
    str     r0, [lr, #8]
    str     r1, [r3, #0x28]
    ldr     r0, [r3]
    ldr     r3, [r3, #0xc]
    bl      func_ov107_020c5af8
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov286_020d3f18
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
