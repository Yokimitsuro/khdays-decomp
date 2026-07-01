extern void func_0203c634(void);
extern void func_ov288_020d42f4(void);
extern void func_ov288_020d4188(void);
extern void func_ov288_020d42b0(void);

asm void func_ov288_020d40ec(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r4, r0
    ldr     lr, [r4, #4]
    mov     ip, #0
    ldr     r1, [lr]
    sub     r3, ip, #1
    strb    ip, [r1, #0x1c6]
    ldr     r1, [lr]
    ldr     r2, =func_ov288_020d42f4
    strb    r3, [r1, #0x1c7]
    ldr     r3, [lr]
    mov     r1, #1
    add     r3, r3, #0xb0
    str     r3, [lr, #0xc]
    ldr     r3, [lr]
    ldr     r3, [r3, #0x388]
    ldr     r6, [r3, #8]
    mov     r5, r6, lsl #0x18
    mov     r5, r5, lsr #0x18
    bic     r5, r5, #1
    bic     r6, r6, #0xff
    and     r5, r5, #0xff
    orr     r5, r6, r5
    str     r5, [r3, #8]
    ldr     r3, [lr]
    str     ip, [r3, #0x394]
    bl      func_0203c634
    ldr     r2, =func_ov288_020d4188
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov288_020d42b0
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, pc}
}
