extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);

asm void func_ov295_020d4274(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    ldr     r1, [pc, #0xb0]
    ldr     r0, [r4]
    mov     r2, #4
    ldrh    ip, [r0, #0x60]
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    bic     r3, r3, #1
    mov     r3, r3, lsl #0x10
    mov     r3, r3, lsr #0x10
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #0x10
    strh    r3, [r0, #0x60]
    ldr     ip, [r4]
    ldrh    r3, [ip, #0x60]
    mov     r0, r3, lsl #0x10
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #0x82
    bic     r3, r3, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, r3, r0, lsr #0x10
    strh    r0, [ip, #0x60]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r3, [r0, #0xae]
    orr     r3, r3, #3
    strh    r3, [r0, #0xae]
    ldr     r0, [r4]
    ldr     ip, [r0, #0x388]
    ldr     r3, [ip, #8]
    mov     r0, r3, lsl #0x18
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #1
    bic     r3, r3, #0xff
    and     r0, r0, #0xff
    orr     r0, r3, r0
    str     r0, [ip, #8]
    ldmia   r4, {r0, r3}
    bl      func_ov107_020c5af8
    ldr     r0, [r4]
    mov     r2, #0
    strb    r2, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
    dcd     0x00000171
}
