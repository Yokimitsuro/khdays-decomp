extern void func_ov107_020c89e8(void);
extern void func_ov107_020c5af8(void);

asm int func_ov296_020d588c(void *r0, int r1, void *r2)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    add     r1, r6, #0x200
    ldrsh   r1, [r1, #0x1a]
    ldr     r4, [r6, #0x214]
    mov     r5, r2
    cmp     r1, #0
    movle   r0, #0
    ldmlefd sp!, {r4, r5, r6, pc}
    mov     r1, r5
    bl      func_ov107_020c89e8
    str     r0, [r5, #0x28]
    add     r1, r6, #0x200
    ldrsh   r2, [r1, #0x1a]
    subs    r0, r2, r0
    movmi   r1, #0
    bmi     _L_0050
    ldrsh   r1, [r1, #0x18]
    cmp     r0, r1
    movle   r1, r0
_L_0050:
    add     r0, r6, #0x200
    strh    r1, [r0, #0x1a]
    ldrsh   r0, [r0, #0x1a]
    cmp     r0, #0
    ldreq   r0, [r4]
    moveq   r1, #3
    streqb  r1, [r0, #0x1c7]
    ldr     r0, [r5, #0x28]
    cmp     r0, #0
    ble     _L_014c
    ldr     r0, [r5]
    mov     r1, r0, lsl #0x10
    mov     r1, r1, lsr #0x10
    tst     r1, #8
    beq     _L_00a0
    tst     r1, #0x80
    beq     _L_00a0
    mov     r0, r0, lsr #0x10
    cmp     r0, #0x80
    beq     _L_014c
_L_00a0:
    tst     r1, #0x22
    ldrb    r1, [r4, #0xc]
    mov     r0, r1, lsl #0x1f
    beq     _L_0100
    mov     r0, r0, lsr #0x1f
    add     r0, r0, #1
    and     r0, r0, #0xff
    bic     r1, r1, #1
    and     r0, r0, #1
    orr     r1, r1, r0
    and     r0, r1, #0xff
    mov     r0, r0, lsl #0x1f
    mov     r0, r0, lsr #0x1f
    strb    r1, [r4, #0xc]
    tst     r0, #1
    movne   r0, #2
    moveq   r0, #3
    mov     r2, r0, lsl #0x10
    ldr     r3, [r4, #4]
    ldr     r1, [pc, #0x60]
    mov     r0, r6
    mov     r2, r2, lsr #0x10
    bl      func_ov107_020c5af8
    b       _L_014c
_L_0100:
    mov     r0, r0, lsr #0x1f
    add     r0, r0, #1
    and     r0, r0, #0xff
    bic     r1, r1, #1
    and     r0, r0, #1
    orr     r1, r1, r0
    and     r0, r1, #0xff
    mov     r0, r0, lsl #0x1f
    mov     r0, r0, lsr #0x1f
    strb    r1, [r4, #0xc]
    tst     r0, #1
    moveq   r0, #1
    movne   r0, #0
    mov     r2, r0, lsl #0x10
    ldr     r3, [r4, #4]
    ldr     r1, [pc, #0x10]
    mov     r0, r6
    mov     r2, r2, lsr #0x10
    bl      func_ov107_020c5af8
_L_014c:
    mov     r0, #1
    ldmfd   sp!, {r4, r5, r6, pc}
    dcd     0x00000171
}
