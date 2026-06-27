extern void func_ov241_020d02a0(void);
extern void func_01fffde0(void);
extern void func_ov022_020ad838(void);
extern void func_0203c634(void);
extern void func_ov241_020d075c(void);
extern void func_ov241_020d0818(void);
extern void func_ov241_020d083c(void);
extern void func_ov241_020d0a30(void);
extern void func_ov241_020d0c08(void);

asm void func_ov241_020d0514(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrsb   r0, [r0, #0xc6]
    cmp     r0, #3
    cmpne   r0, #2
    cmpne   r0, #4
    bne     _afterCall
    mov     r0, r5
    bl      func_ov241_020d02a0
    str     r0, [r4, #0x30]
    cmp     r0, #0
    beq     _afterCall
    ldrb    r0, [r0, #0x1b4]
    bl      func_01fffde0
    ldr     r1, [r0]
    ldr     r0, [r0, #4]
    and     r1, r1, #0x10000
    and     r0, r0, #0
    cmp     r0, #0
    cmpeq   r1, #0
    beq     _branch80
    ldr     r1, [r4]
    ldr     r2, [r1, #0x3b8]
    cmp     r2, #0
    beq     _afterCall
    ldr     r0, [r4, #0x30]
    ldrb    r0, [r0, #0x1b4]
    blx     r2
    b       _afterCall
_branch80:
    ldr     r0, [r4, #0x30]
    mov     r1, #1
    ldr     r0, [r0, #0x18c]
    bl      func_ov022_020ad838
    ldr     r0, [r4]
    mov     r1, #6
    strb    r1, [r0, #0x1c7]
_afterCall:
    ldr     r2, [r4]
    mvn     r1, #0
    add     r0, r2, #0x100
    ldrsb   r0, [r0, #0xc7]
    cmp     r0, r1
    beq     _switchExit
    strb    r0, [r2, #0x1c6]
    ldr     r0, [r4]
    mov     r1, #0
    ldrh    r3, [r0, #0x60]
    mov     r2, r3, lsl #0x10
    mov     r2, r2, lsr #0x18
    bic     r2, r2, #0xce
    mov     r2, r2, lsl #0x10
    mov     r2, r2, lsr #0x10
    bic     r3, r3, #0xff00
    mov     r2, r2, lsl #0x18
    orr     r2, r3, r2, lsr #0x10
    strh    r2, [r0, #0x60]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r2, [r0, #0xae]
    bic     r2, r2, #1
    strh    r2, [r0, #0xae]
_loopFc:
    ldr     r0, [r4]
    add     r0, r0, r1, lsl #2
    ldr     r2, [r0, #0x38c]
    add     r1, r1, #1
    ldr     r0, [r2, #0x5c]
    cmp     r1, #3
    bic     r0, r0, #2
    str     r0, [r2, #0x5c]
    blt     _loopFc
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrsb   r0, [r0, #0xc6]
    cmp     r0, #6
    addls   pc, pc, r0, lsl #2
    b       _switchExit
    b       _case0
    b       _case1
    b       _case2
    b       _case3
    b       _switchExit
    b       _switchExit
    b       _case6
_case0:
    ldr     r2, =func_ov241_020d075c
    mov     r0, r5
    mov     r1, #1
    bl      func_0203c634
    b       _switchExit
_case1:
    ldr     r2, =func_ov241_020d0818
    mov     r0, r5
    mov     r1, #1
    bl      func_0203c634
    b       _switchExit
_case2:
    ldr     r2, =func_ov241_020d083c
    mov     r0, r5
    mov     r1, #1
    bl      func_0203c634
    b       _switchExit
_case3:
    ldr     r2, =func_ov241_020d0a30
    mov     r0, r5
    mov     r1, #1
    bl      func_0203c634
    b       _switchExit
_case6:
    ldr     r2, =func_ov241_020d0c08
    mov     r0, r5
    mov     r1, #1
    bl      func_0203c634
_switchExit:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r3, r4, r5, pc}
}
