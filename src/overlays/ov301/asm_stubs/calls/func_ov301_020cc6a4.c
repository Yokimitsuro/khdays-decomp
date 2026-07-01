extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov301_020cc6a4(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     ip, [r4, #4]
    ldr     r3, [ip]
    ldrh    r0, [r3, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    ldmeqfd sp!, {r4, pc}
    add     r0, r3, #0x100
    ldrsb   r0, [r0, #0xc9]
    mov     r1, #0
    mov     r2, #1
    strb    r0, [r3, #0x1c7]
    ldr     r0, [ip]
    bl      func_ov107_020c9264
    ldrsb   r1, [r4, #0x20]
    mov     r0, r4
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
