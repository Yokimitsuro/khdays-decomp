extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern void *data_ov071_020b9a1c;

asm void func_ov071_020b83ec(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    add     r0, r5, #0x2f8
    add     r4, r0, #0x2000
    mov     r0, #0
    strb    r0, [r4, #0x334]
    ldrb    r0, [r5, #9]
    mov     r1, #1
    bl      func_ov022_020b15b0
    ldr     r2, [r5, #0x20]
    ldrb    r1, [r5, #9]
    add     r3, r2, #4
    ldr     r0, =data_ov071_020b9a1c
    mov     r2, #0
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x340]
    add     r0, r5, #0xda0
    mov     r1, #0xca
    bl      func_ov022_020b1cec
    ldrb    r0, [r4, #0x334]
    orr     r0, r0, #9
    strb    r0, [r4, #0x334]
    ldmfd   sp!, {r3, r4, r5, pc}
}
