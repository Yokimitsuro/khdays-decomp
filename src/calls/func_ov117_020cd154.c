extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov117_020cd1b0(void);

asm void func_ov117_020cd154(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4]
    mov     r1, #1
    ldr     r2, [r0, #0x2c]
    mov     r0, #0x1e
    mul     ip, r2, r0
    ldr     r3, =0x66666667
    mov     r0, ip, lsr #0x1f
    smull   r2, ip, r3, ip
    ldr     r2, [r4, #4]
    add     ip, r0, ip, asr #2
    str     ip, [r2, #0x28]
    ldr     r0, [r2]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov117_020cd1b0
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
