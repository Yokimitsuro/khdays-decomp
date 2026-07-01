extern void func_ov117_020cc1c8(void *);
extern void func_ov107_020c7ca4(void *);

asm void func_ov117_020cc354(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldrh    r0, [r4, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #0x80
    bne     _L24
    tst     r0, #1
    bne     _L2c
_L24:
    mov     r0, r4
    bl      func_ov117_020cc1c8
_L2c:
    mov     r0, r4
    bl      func_ov107_020c7ca4
    ldmfd   sp!, {r4, pc}
}
