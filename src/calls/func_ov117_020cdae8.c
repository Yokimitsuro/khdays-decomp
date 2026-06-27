extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov117_020cdb7c(void);

asm void func_ov117_020cdae8(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4, #4]
    mov     r1, #3
    ldr     lr, [r0]
    mov     r2, #0
    ldrh    ip, [lr, #0x60]
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    orr     r3, r3, #0x4c
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #0x10
    strh    r3, [lr, #0x60]
    ldr     r3, [r0]
    add     r3, r3, #0x100
    ldrh    ip, [r3, #0xae]
    orr     ip, ip, #1
    strh    ip, [r3, #0xae]
    ldr     r3, [r0]
    ldr     lr, [r3, #0x388]
    ldr     ip, [lr, #8]
    mov     r3, ip, lsl #0x18
    mov     r3, r3, lsr #0x18
    bic     r3, r3, #1
    bic     ip, ip, #0xff
    and     r3, r3, #0xff
    orr     r3, ip, r3
    str     r3, [lr, #8]
    ldr     r0, [r0]
    bl      func_ov107_020c9264
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov117_020cdb7c
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
