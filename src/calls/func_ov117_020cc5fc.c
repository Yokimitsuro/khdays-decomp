extern void func_0203c634(void);
extern void data_020420f8(void);
extern void func_ov117_020cc9fc(void);
extern void func_ov117_020cc6e8(void);
extern void func_ov117_020cc8f8(void);

asm void func_ov117_020cc5fc(void *r0)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r4, r0
    ldr     lr, [r4, #4]
    mov     r2, #0
    ldr     r1, [lr]
    ldr     r0, =data_020420f8
    strb    r2, [r1, #0x1c6]
    ldr     r1, [lr]
    sub     r2, r2, #1
    strb    r2, [r1, #0x1c7]
    ldr     r1, [lr]
    add     r6, lr, #8
    ldr     ip, [r1, #0x388]
    ldmia   r0, {r0, r1, r2, r3}
    ldr     r8, [ip, #8]
    add     r5, lr, #0x18
    mov     r7, r8, lsl #0x18
    mov     r7, r7, lsr #0x18
    bic     r7, r7, #1
    bic     r8, r8, #0xff
    and     r7, r7, #0xff
    orr     r7, r8, r7
    str     r7, [ip, #8]
    ldr     r7, [lr]
    add     r7, r7, #0x74
    str     r7, [lr, #0x44]
    ldr     r7, [lr]
    ldr     r7, [r7, #0x384]
    add     r7, r7, #0xad
    str     r7, [lr, #0x48]
    ldr     ip, [lr]
    ldrh    r7, [ip, #0x60]
    mov     lr, r7, lsl #0x10
    mov     lr, lr, lsr #0x18
    orr     lr, lr, #6
    bic     r7, r7, #0xff00
    mov     lr, lr, lsl #0x18
    orr     r7, r7, lr, lsr #0x10
    strh    r7, [ip, #0x60]
    stmia   r6, {r0, r1, r2, r3}
    ldmia   r6, {r0, r1, r2, r3}
    stmia   r5, {r0, r1, r2, r3}
    ldr     r2, =func_ov117_020cc9fc
    mov     r0, r4
    mov     r1, #1
    bl      func_0203c634
    ldr     r2, =func_ov117_020cc6e8
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    mov     r0, r4
    mov     r1, #2
    ldr     r2, =func_ov117_020cc8f8
    bl      func_0203c634
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
