extern void FX_Sqrt(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov286_020d409c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    add     r1, sp, #0
    ldr     r0, [r4]
    bl      func_ov107_020cab14
    movs    r7, r0
    str     r0, [r4, #0x18]
    ldmeqfd sp!, {r3, r4, r5, r6, r7, pc}
    ldr     r6, [r4]
    ldr     r0, [sp]
    bl      FX_Sqrt
    ldr     r2, [r7, #0x80]
    ldr     r1, [r6, #0x80]
    add     r1, r2, r1
    sub     r1, r0, r1
    mov     r0, #0xc9
    str     r1, [sp]
    bl      func_02023eb4
    adds    r0, r0, #0
    bne     _L74
    ldr     r0, [r4]
    mov     r1, #4
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_L74:
    ldr     r0, [sp]
    cmp     r0, #0x2000
    bge     _Ldc
    ldr     r1, [r4]
    ldr     r0, [r5]
    ldrb    r2, [r1, #0x19e]
    ldr     r1, =0x66666667
    ldr     r3, [r4, #0x28]
    mov     ip, r2, lsl #0xc
    ldr     r2, [r0, #0x2c]
    smull   r0, lr, r1, ip
    mov     r0, ip, lsr #0x1f
    add     lr, r0, lr, asr #2
    add     r1, r3, r2
    rsb     r0, lr, #0x1000
    str     r1, [r4, #0x28]
    cmp     r1, r0
    ldmltfd sp!, {r3, r4, r5, r6, r7, pc}
    ldr     r0, [r4]
    mov     r1, #4
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_Ldc:
    mov     r0, #0
    str     r0, [r4, #0x28]
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
