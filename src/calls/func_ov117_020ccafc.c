extern void func_ov107_020cab14(void);
extern void func_ov117_020cc5c0(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov117_020ccbcc(void);

asm void func_ov117_020ccafc(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #0
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r0, r2, lsl #0x10
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #0x8c
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    bic     r2, r2, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, r2, r0, lsr #0x10
    strh    r0, [r3, #0x60]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r2, [r0, #0xae]
    orr     r2, r2, #1
    strh    r2, [r0, #0xae]
    ldr     r0, [r4]
    ldr     r3, [r0, #0x388]
    ldr     r2, [r3, #8]
    mov     r0, r2, lsl #0x18
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #1
    bic     r2, r2, #0xff
    and     r0, r0, #0xff
    orr     r0, r2, r0
    str     r0, [r3, #8]
    ldr     r0, [r4]
    bl      func_ov107_020cab14
    str     r0, [r4, #4]
    cmp     r0, #0
    beq     _skip
    mov     r0, r4
    add     r1, r4, #0x18
    bl      func_ov117_020cc5c0
    add     r0, r4, #0x18
    add     ip, r4, #8
    ldmia   r0, {r0, r1, r2, r3}
    stmia   ip, {r0, r1, r2, r3}
_skip:
    mov     r1, #0
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov117_020ccbcc
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
