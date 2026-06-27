extern void func_ov031_020b4694(void);
extern void func_02033d0c(void);
extern void func_02030788(void);
extern void *data_ov031_020b4cd4;

asm void func_ov031_020b453c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov     r10, r0
    ldrb    r0, [r10, #0x19]
    mov     r6, #0
    ldr     r5, [r10, #8]
    mov     r9, r1
    mov     r7, r6
    cmp     r0, #0
    ldmlefd sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    ldr     r11, =data_ov031_020b4cd4
    mov     r8, r6
_loop:
    ldr     r0, [r10, #0xc]
    add     r4, r0, r8
    ldrsb   r0, [r4, #2]
    cmp     r0, #0
    beq     _skip
    cmp     r0, #2
    beq     _case2
    mov     r1, r4
    ldr     r3, [r11, r0, lsl #2]
    mov     r0, r10
    mov     r2, r9
    blx     r3
    b       _skip
_case2:
    mov     r0, r10
    mov     r1, r4
    mov     r2, r9
    bl      func_ov031_020b4694
    ldrsb   r0, [r4, #2]
    cmp     r0, #4
    ldreq   r0, [r10]
    cmpeq   r0, #0
    cmpeq   r6, #0
    bne     _skip
    ldrb    r0, [r5, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _afterdebug
    mov     r1, #0
    mov     r0, #0xcb
    add     r2, r4, #0xcc
    mov     r3, r1
    bl      func_02033d0c
_afterdebug:
    bl      func_02030788
    cmp     r0, #0
    bne     _set6
    ldr     r1, [r5]
    tst     r1, #0x10000
    bne     _set6
    mov     r0, #3
    strb    r0, [r5, #0x47a]
    mov     r0, #0
    strb    r0, [r5, #0x47b]
_set6:
    mov     r6, #1
_skip:
    ldrb    r0, [r10, #0x19]
    add     r8, r8, #0x1c8
    add     r7, r7, #1
    cmp     r7, r0
    blt     _loop
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
