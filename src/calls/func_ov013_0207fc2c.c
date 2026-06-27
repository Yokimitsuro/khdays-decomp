extern int func_ov022_020893f4(int a, int b, int c);
extern int func_ov022_0208963c(int a);

asm void func_ov013_0207fc2c(void *r0)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    mov     r9, r0
    ldr     r1, [r9, #0x6bc]
    cmp     r1, #0
    ldmltfd sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    ldrb    r0, [r9, #0x7d1]
    cmp     r0, r1
    bne     _L3c
    ldr     r1, [r9, #0x464]
    ldr     r0, [r9, #0x468]
    and     r1, r1, #0x80000000
    and     r0, r0, #0
    cmp     r0, #0
    cmpeq   r1, #0
    beq     _L44
_L3c:
    mov     r0, #0
    strb    r0, [r9, #0x7d0]
_L44:
    ldr     r1, [r9, #0x6bc]
    add     r0, r9, r1, lsl #2
    ldr     r7, [r0, #0x6c0]
    cmp     r7, #0
    ldmeqfd sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    strb    r1, [r9, #0x7d1]
    ldrb    r0, [r7, #1]
    mov     r8, #0
    cmp     r0, #0
    ldmlefd sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    add     r10, r9, #0x8c
    mov     r4, #0x1000
    mov     r5, r8
    mov     r6, #1
_L7c:
    ldr     r0, [r7, #4]
    ldr     r1, [r0, r8, lsl #2]
    ldr     r0, [r1, #0xc]
    ldrh    r0, [r0]
    cmp     r0, #0xf
    cmpne   r0, #2
    cmpne   r0, #0x1c
    bne     _Lec
    ldr     r1, [r1]
    ldr     r0, [r9, #0x7b0]
    cmp     r1, r0
    bgt     _Lec
    ldrb    r0, [r9, #0x7d0]
    tst     r0, r6, lsl r8
    bne     _Lec
    orr     r0, r0, r6, lsl r8
    strb    r0, [r9, #0x7d0]
    ldr     r0, [r9, #0x7c8]
    mov     r2, r5
    add     r1, r10, #0x400
    bl      func_ov022_020893f4
    movs    r1, r0
    bmi     _Lec
    ldr     r0, [r9, #0x7c8]
    bl      func_ov022_0208963c
    str     r4, [r0, #0xb8]
    str     r4, [r0, #0xb4]
    str     r4, [r0, #0xb0]
_Lec:
    ldrb    r0, [r7, #1]
    add     r8, r8, #1
    cmp     r8, r0
    blt     _L7c
    ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
