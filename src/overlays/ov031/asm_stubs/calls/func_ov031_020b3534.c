extern void func_ov031_020b39d4(void);
extern void func_ov022_020a4490(void);
extern void func_ov031_020b3a20(void);
extern void func_ov022_020a384c(void);

asm void func_ov031_020b3534(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    mov     r4, r1
    cmp     r4, #0x2e
    add     r1, r5, #0x2c
    beq     _eq2e
    cmp     r4, #0x2f
    cmpne   r4, #0x30
    beq     _eq2f30
    b       _tail
_eq2e:
    ldr     r2, [r5, #0x6bc]
    cmp     r4, r2
    beq     _tail
    add     r1, r1, #0x2c00
    bl      func_ov031_020b39d4
    b       _tail
_eq2f30:
    ldr     r0, [r5, #0x6bc]
    cmp     r4, r0
    beq     _tail
    cmp     r4, #0x2f
    add     r3, r5, #0x2000
    bne     _ne2f
    mov     r1, #0
    str     r1, [r3, #0xc2c]
    mov     r12, #0x9000
    mov     r0, r5
    mov     r1, #0xcb
    mov     r2, #2
    str     r12, [r3, #0xc34]
    bl      func_ov022_020a4490
    add     r0, r5, #0xd50
    add     r0, r0, #0x2000
    mov     r1, #0
    bl      func_ov031_020b3a20
    b       _tail
_ne2f:
    mov     r1, #1
    str     r1, [r3, #0xc2c]
    mov     r12, #0x12000
    mov     r0, r5
    mov     r1, #0xcb
    mov     r2, #3
    str     r12, [r3, #0xc34]
    bl      func_ov022_020a4490
    add     r0, r5, #0x38
    add     r0, r0, #0x2c00
    mov     r1, #0x9000
    bl      func_ov031_020b3a20
    add     r0, r5, #0xd50
    add     r0, r0, #0x2000
    mov     r1, #0x9000
    bl      func_ov031_020b3a20
_tail:
    mov     r0, r5
    mov     r1, r4
    bl      func_ov022_020a384c
    ldmfd   sp!, {r3, r4, r5, pc}
}
