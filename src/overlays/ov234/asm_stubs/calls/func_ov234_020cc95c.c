extern void func_0203c634(int a, int b, int c);
extern void func_ov234_020ccedc(void);
extern void func_ov234_020ccf4c(void);
extern void func_ov234_020ccf68(void);
extern void func_ov234_020cd0d4(void);

asm void func_ov234_020cc95c(void *r0)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r2, #0
    ldr     r3, [r4]
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc7]
    cmp     r1, r2
    beq     _L108
    strb    r1, [r3, #0x1c6]
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #0xc6
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #16
    strh    r1, [r3, #0x60]
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
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x40
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #16
    strh    r1, [r3, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #5
    addls   pc, pc, r1, lsl #2
    b       _L108
    b       _Lcc
    b       _L108
    b       _Ldc
    b       _Lfc
    b       _L108
    b       _Lec
_Lcc:
    ldr     r2, =func_ov234_020ccedc
    mov     r1, #1
    bl      func_0203c634
    b       _L108
_Ldc:
    ldr     r2, =func_ov234_020ccf4c
    mov     r1, #1
    bl      func_0203c634
    b       _L108
_Lec:
    ldr     r2, =func_ov234_020ccf68
    mov     r1, #1
    bl      func_0203c634
    b       _L108
_Lfc:
    ldr     r2, =func_ov234_020cd0d4
    mov     r1, #1
    bl      func_0203c634
_L108:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
}
