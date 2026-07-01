extern void func_01fffe14(void);
extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov234_020cc95c(void);
extern void func_ov234_020cca84(void);
extern void func_ov234_020ccedc(void);

asm void func_ov234_020cc864(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    sub     sp, sp, #8
    mov     r4, r0
    ldr     r0, [r4, #4]
    mov     ip, #0
    ldr     r1, [r0]
    sub     r3, ip, #1
    strb    ip, [r1, #0x1c6]
    ldr     r2, [r0]
    sub     r1, ip, #0x280
    strb    r3, [r2, #0x1c7]
    strh    ip, [r0, #0x70]
    str     r1, [r0, #0x54]
    sub     r1, ip, #0x38
    str     r1, [r0, #0x58]
    mov     r1, #0xe00
    str     r1, [r0, #0x5c]
    mov     r1, #0x400
    str     r1, [r0, #0x60]
    ldr     r1, [r0]
    add     r1, r1, #0xb0
    str     r1, [r0, #8]
    ldr     r3, [r0]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #6
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #0x10
    strh    r1, [r3, #0x60]
    ldr     r5, [r0]
    bl      func_01fffe14
    and     r0, r0, #0xff
    str     r0, [sp, #4]
    add     r0, r5, #0x74
    sub     r3, sp, #8
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r5
    mov     r1, #5
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
    ldr     r2, =func_ov234_020ccedc
    mov     r0, r4
    mov     r1, #1
    bl      func_0203c634
    mov     r0, r4
    mov     r1, #0
    ldr     r2, =func_ov234_020cc95c
    bl      func_0203c634
    mov     r0, r4
    mov     r1, #2
    ldr     r2, =func_ov234_020cca84
    bl      func_0203c634
    add     sp, sp, #8
    ldmfd   sp!, {r3, r4, r5, pc}
}
