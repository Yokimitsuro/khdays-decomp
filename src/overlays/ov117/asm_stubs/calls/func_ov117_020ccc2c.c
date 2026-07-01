extern void func_ov107_020c9264(void);
extern int func_02023eb4(int);
extern void func_0203c634(void);
extern void func_ov117_020cccb4(void);

asm void func_ov117_020ccc2c(void *r0)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r4, r0
    ldr     r0, [r4]
    ldr     r3, =0x66666667
    ldr     r2, [r0, #0x2c]
    mov     r0, #0x1e
    mul     ip, r2, r0
    mov     r0, ip, lsr #0x1f
    smull   r2, ip, r3, ip
    mov     r1, #1
    ldr     r5, [r4, #4]
    add     ip, r0, ip, asr #3
    str     ip, [r5, #0x28]
    ldr     r0, [r5]
    mov     r2, r1
    bl      func_ov107_020c9264
    mov     r0, #2
    bl      func_02023eb4
    adds    r0, r0, #0
    mvnne   r6, #0
    ldr     r0, =0x00000101
    moveq   r6, #1
    bl      func_02023eb4
    add     r1, r0, #0
    mul     r0, r1, r6
    str     r0, [r5, #0x5c]
    ldrsb   r1, [r4, #0x20]
    ldr     r2, =func_ov117_020cccb4
    mov     r0, r4
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, pc}
}
