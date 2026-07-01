extern void func_0203c634(void);
extern void func_ov286_020d3dac(void);
extern void func_ov286_020d3e50(void);
extern void func_ov286_020d4038(void);
extern void func_ov286_020d4188(void);
extern void func_ov286_020d43ec(void);
extern void func_ov286_020d44b4(void);

asm void func_ov286_020d3bd0(void)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r3, #0
    ldr     r1, [r4]
    add     r2, r1, #0x100
    ldrsb   r2, [r2, #0xc7]
    cmp     r2, r3
    beq     _L120
    ldrh    r3, [r1, #0x60]
    mov     r2, r3, lsl #0x10
    mov     r2, r2, lsr #0x18
    bic     r2, r2, #0xce
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
    ldr     r3, [r1, #0x38c]
    ldr     r2, [r3, #8]
    mov     r1, r2, lsl #0x18
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #1
    bic     r2, r2, #0xff
    and     r1, r1, #0xff
    orr     r1, r2, r1
    str     r1, [r3, #8]
    ldr     r2, [r4]
    add     r1, r2, #0x100
    ldrsb   r1, [r1, #0xc7]
    strb    r1, [r2, #0x1c6]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #5
    addls   pc, pc, r1, lsl #2
    b       _L120
    b       _Lc4
    b       _Ld4
    b       _Le4
    b       _L104
    b       _Lf4
    b       _L114
_Lc4:
    ldr     r2, =func_ov286_020d3dac
    mov     r1, #1
    bl      func_0203c634
    b       _L120
_Ld4:
    ldr     r2, =func_ov286_020d3e50
    mov     r1, #1
    bl      func_0203c634
    b       _L120
_Le4:
    ldr     r2, =func_ov286_020d4038
    mov     r1, #1
    bl      func_0203c634
    b       _L120
_Lf4:
    ldr     r2, =func_ov286_020d4188
    mov     r1, #1
    bl      func_0203c634
    b       _L120
_L104:
    ldr     r2, =func_ov286_020d43ec
    mov     r1, #1
    bl      func_0203c634
    b       _L120
_L114:
    ldr     r2, =func_ov286_020d44b4
    mov     r1, #1
    bl      func_0203c634
_L120:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
}
