extern void func_0203c634(void);
extern void func_ov288_020d42f4(void);
extern void func_ov288_020d43dc(void);
extern void func_ov288_020d458c(void);
extern void func_ov288_020d4bcc(void);
extern void func_ov288_020d5174(void);

asm void func_ov288_020d4188(void)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r2, #0
    ldr     r3, [r4]
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc7]
    cmp     r1, r2
    ldmeqfd sp!, {r4, pc}
    strb    r1, [r3, #0x1c6]
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #0x80
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #16
    strh    r1, [r3, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrh    r2, [r1, #0xae]
    bic     r2, r2, #0x13
    strh    r2, [r1, #0xae]
    ldr     r1, [r4]
    ldr     r3, [r1, #0x388]
    ldr     r2, [r3, #8]
    mov     r1, r2, lsl #0x18
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #1
    bic     r2, r2, #0xff
    and     r1, r1, #0xff
    orr     r1, r2, r1
    str     r1, [r3, #8]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #4
    addls   pc, pc, r1, lsl #2
    b       _L_0104
    b       _L_00b8
    b       _L_00c8
    b       _L_00d8
    b       _L_00f8
    b       _L_00e8
_L_00b8:
    ldr     r2, =func_ov288_020d42f4
    mov     r1, #1
    bl      func_0203c634
    b       _L_0104
_L_00c8:
    ldr     r2, =func_ov288_020d43dc
    mov     r1, #1
    bl      func_0203c634
    b       _L_0104
_L_00d8:
    ldr     r2, =func_ov288_020d458c
    mov     r1, #1
    bl      func_0203c634
    b       _L_0104
_L_00e8:
    ldr     r2, =func_ov288_020d4bcc
    mov     r1, #1
    bl      func_0203c634
    b       _L_0104
_L_00f8:
    ldr     r2, =func_ov288_020d5174
    mov     r1, #1
    bl      func_0203c634
_L_0104:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
}
