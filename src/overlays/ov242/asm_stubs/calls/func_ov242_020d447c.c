extern void func_02023eb4(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov242_020d452c(void);
extern void func_ov242_020d4608(void);
extern void func_ov242_020d45d4(void);

asm void func_ov242_020d447c(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #0x14
    ldr     r0, [r4]
    ldr     r2, [r4, #0x24]
    ldr     r3, [r0, #0x3a4]
    mov     r0, #0x64
    mla     r6, r2, r1, r3
    ldr     r1, [r6, #0xc]
    str     r1, [r4, #0x2c]
    bl      func_02023eb4
    ldr     r1, [r6, #0x10]
    cmp     r0, r1
    bhs     _L_0060
    ldr     r0, [r4]
    mov     r1, #3
    mov     r2, #0
    bl      func_ov107_020c9264
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov242_020d452c
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, pc}
_L_0060:
    ldr     r0, [r4, #0x2c]
    cmp     r0, #0x100
    bgt     _L_0080
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov242_020d4608
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, pc}
_L_0080:
    ldr     r0, [r4]
    mov     r1, #0
    mov     r2, #1
    bl      func_ov107_020c9264
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov242_020d45d4
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, pc}
}
