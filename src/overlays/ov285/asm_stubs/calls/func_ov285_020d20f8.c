extern int func_ov107_020cab14(void *, int);
extern void VEC_Subtract(void *, void *, void *);
extern int func_020050b4(int, int);
extern void func_ov107_020c9264(void *);
extern void func_0203c634(void *r0, int r1, void *r2);
extern void func_ov285_020d21c8(void);

asm void func_ov285_020d20f8(void *r0)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0xc
    mov     r5, r0
    ldmia   r5, {r0, r4}
    ldr     r1, [r0, #0x2c]
    ldr     r2, [r4, #0x28]
    ldr     r0, =0x000006ee
    add     r1, r2, r1
    cmp     r1, r0
    addlt   sp, sp, #0xc
    str     r1, [r4, #0x28]
    ldmltfd sp!, {r4, r5, pc}
    ldr     r0, [r4]
    mov     r1, #0
    bl      func_ov107_020cab14
    str     r0, [r4, #0x18]
    cmp     r0, #0
    beq     _skip
    ldr     r1, [r4, #0x10]
    add     r2, sp, #0
    add     r0, r0, #0x74
    bl      VEC_Subtract
    ldr     r0, [sp]
    ldr     r1, [sp, #8]
    bl      func_020050b4
    str     r0, [r4, #8]
    str     r0, [r4, #4]
_skip:
    ldr     r0, [r4]
    mov     r1, #0
    ldrh    ip, [r0, #0x60]
    mov     r2, r1
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    bic     r3, r3, #0xc0
    mov     r3, r3, lsl #0x10
    mov     r3, r3, lsr #0x10
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #0x10
    strh    r3, [r0, #0x60]
    ldr     r0, [r4]
    bl      func_ov107_020c9264
    mov     r0, #0
    str     r0, [r4, #0x28]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov285_020d21c8
    mov     r0, r5
    bl      func_0203c634
    add     sp, sp, #0xc
    ldmfd   sp!, {r4, r5, pc}
}
