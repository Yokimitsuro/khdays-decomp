extern void func_0203c634(void);
extern void func_ov296_020d5b94(void);
extern void func_ov296_020d5c48(void);
extern void func_ov296_020d6094(void);

asm void func_ov296_020d5a84(void *r0)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r3, #0
    ldr     r1, [r4]
    add     r2, r1, #0x100
    ldrsb   r2, [r2, #0xc7]
    cmp     r2, r3
    beq     _L_00f0
    ldrh    r3, [r1, #0x60]
    mov     r2, r3, lsl #0x10
    mov     r2, r2, lsr #0x18
    bic     r2, r2, #0x8a
    mov     r2, r2, lsl #0x10
    mov     r2, r2, lsr #0x10
    bic     r3, r3, #0xff00
    mov     r2, r2, lsl #0x18
    orr     r2, r3, r2, lsr #16
    strh    r2, [r1, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrh    r2, [r1, #0xae]
    bic     r2, r2, #1
    strh    r2, [r1, #0xae]
    ldr     r1, [r4]
    ldr     r3, [r1, #0x388]
    ldr     r2, [r3, #8]
    mov     r1, r2, lsl #0x18
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #1
    bic     r2, r2, #0xff
    and     r1, r1, #0xff
    orr     r1, r2, r1
    str     r1, [r3, #8]
    ldr     r2, [r4]
    add     r1, r2, #0x100
    ldrsb   r1, [r1, #0xc7]
    strb    r1, [r2, #0x1c6]
    ldr     r2, [r4]
    add     r1, r2, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #3
    addls   pc, pc, r1, lsl #2
    b       _L_00f0
    b       _L_00bc
    b       _L_00cc
    b       _L_00d4
    b       _L_00e4
_L_00bc:
    ldr     r2, [pc, #0x3c]
    mov     r1, #1
    bl      func_0203c634
    b       _L_00f0
_L_00cc:
    mov     r1, #2
    strb    r1, [r2, #0x1c6]
_L_00d4:
    ldr     r2, [pc, #0x28]
    mov     r1, #1
    bl      func_0203c634
    b       _L_00f0
_L_00e4:
    ldr     r2, [pc, #0x1c]
    mov     r1, #1
    bl      func_0203c634
_L_00f0:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
    dcd     func_ov296_020d5b94
    dcd     func_ov296_020d5c48
    dcd     func_ov296_020d6094
}
