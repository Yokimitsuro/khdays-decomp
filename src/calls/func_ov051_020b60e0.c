extern void func_ov022_02095524(void);
extern void func_0202accc(void);
extern void func_ov051_020b6ef0(void);
extern void func_ov051_020b6fa0(void);
extern void *data_ov051_020b7380;

asm void func_ov051_020b60e0(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    ldr     r2, [r4, #0x464]
    ldr     r1, [r4, #0x468]
    ldr     r0, =data_ov051_020b7380
    and     r1, r1, #0
    and     r2, r2, #0x10000
    cmp     r1, #0
    cmpeq   r2, #0
    ldr     r5, [r0]
    bne     _skip
    add     r0, r4, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    bne     _skip
    ldr     r0, [r4, #0x6bc]
    cmp     r0, #0x2e
    beq     _skip
    add     r0, r4, #0xf10
    add     r2, r4, #0xff0
    mov     r1, #1
    mov     r3, #0
    bl      func_0202accc
_skip:
    add     r0, r4, #0x2a00
    ldrsh   r2, [r0, #0xba]
    add     r1, r5, #0x2c
    mov     r0, r4
    add     r1, r1, #0x2c00
    bl      func_ov051_020b6ef0
    add     r1, r5, #0x2c
    mov     r0, r4
    add     r1, r1, #0x2c00
    bl      func_ov051_020b6fa0
    ldmfd   sp!, {r3, r4, r5, pc}
}
