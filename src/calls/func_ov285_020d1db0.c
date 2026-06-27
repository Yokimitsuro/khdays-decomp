extern void func_0203c634(void);
extern void func_ov285_020d1f8c(void);
extern void func_ov285_020d2030(void);
extern void func_ov285_020d2218(void);
extern void func_ov285_020d2368(void);
extern void func_ov285_020d25cc(void);
extern void func_ov285_020d2694(void);

asm void func_ov285_020d1db0(void *r0)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r3, #0
    ldr     r1, [r4]
    add     r2, r1, #0x100
    ldrsb   r2, [r2, #0xc7]
    cmp     r2, r3
    beq     _exit
    ldrh    r3, [r1, #0x60]
    mov     r2, r3, lsl #0x10
    mov     r2, r2, lsr #0x18
    bic     r2, r2, #0xce
    mov     r2, r2, lsl #0x10
    mov     r2, r2, lsr #0x10
    bic     r3, r3, #0xff00
    mov     r2, r2, lsl #0x18
    orr     r2, r3, r2, lsr #0x10
    strh    r2, [r1, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrh    r2, [r1, #0xae]
    bic     r2, r2, #1
    strh    r2, [r1, #0xae]
    ldr     r1, [r4]
    ldr     r3, [r1, #0x38c]
    ldr     r2, [r3, #8]
    mov     r1, r2, lsl #0x18
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #1
    bic     r2, r2, #0xff
    and     r1, r1, #0xff
    orr     r1, r2, r1
    str     r1, [r3, #8]
    ldr     r2, [r4]
    add     r1, r2, #0x100
    ldrsb   r1, [r1, #0xc7]
    strb    r1, [r2, #0x1c6]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #5
    addls   pc, pc, r1, lsl #2
    b       _exit
    b       _case0
    b       _case1
    b       _case2
    b       _case4
    b       _case3
    b       _case5
_case0:
    ldr     r2, =func_ov285_020d1f8c
    mov     r1, #1
    bl      func_0203c634
    b       _exit
_case1:
    ldr     r2, =func_ov285_020d2030
    mov     r1, #1
    bl      func_0203c634
    b       _exit
_case2:
    ldr     r2, =func_ov285_020d2218
    mov     r1, #1
    bl      func_0203c634
    b       _exit
_case3:
    ldr     r2, =func_ov285_020d2368
    mov     r1, #1
    bl      func_0203c634
    b       _exit
_case4:
    ldr     r2, =func_ov285_020d25cc
    mov     r1, #1
    bl      func_0203c634
    b       _exit
_case5:
    ldr     r2, =func_ov285_020d2694
    mov     r1, #1
    bl      func_0203c634
_exit:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
}
