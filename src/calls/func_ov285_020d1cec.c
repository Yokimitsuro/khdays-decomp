extern void func_0203c634(void *r0, int r1, void *r2);
extern void func_ov285_020d1f8c(void);
extern void func_ov285_020d1db0(void);
extern void func_ov285_020d1ef8(void);

asm void func_ov285_020d1cec(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    ldr     r3, [r4, #4]
    mov     r2, #0
    ldr     r1, [r3]
    sub     r5, r2, #1
    strb    r2, [r1, #0x1c6]
    ldr     r1, [r3]
    ldr     r2, =func_ov285_020d1f8c
    strb    r5, [r1, #0x1c7]
    ldr     r5, [r3]
    mov     r1, #1
    ldr     r5, [r5, #0x38c]
    ldr     lr, [r5, #8]
    mov     ip, lr, lsl #0x18
    mov     ip, ip, lsr #0x18
    bic     ip, ip, #1
    bic     lr, lr, #0xff
    and     ip, ip, #0xff
    orr     ip, lr, ip
    str     ip, [r5, #8]
    ldr     ip, [r3]
    add     ip, ip, #0xb0
    str     ip, [r3, #0xc]
    ldr     ip, [r3]
    add     ip, ip, #0x74
    str     ip, [r3, #0x10]
    ldr     lr, [r3]
    ldrh    ip, [lr, #0x60]
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    orr     r3, r3, #0x16
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #0x10
    strh    r3, [lr, #0x60]
    bl      func_0203c634
    ldr     r2, =func_ov285_020d1db0
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov285_020d1ef8
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
