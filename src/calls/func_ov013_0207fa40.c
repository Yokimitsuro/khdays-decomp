extern int func_020357f4(int a, int b);
extern int func_ov002_0206f6e4(int a, int b);
extern int func_ov002_0206f04c;
extern int func_ov002_0206f0c8;

asm void func_ov013_0207fa40(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    mvn     r0, #1
    strb    r0, [r4, #0x10]
    ldrsb   r0, [r4, #0x18]
    cmp     r0, #0
    bne     _L58
    ldrsb   r0, [r4, #0x19]
    mov     r5, #0
    strb    r0, [r4, #0x10]
_L28:
    ldrsb   r0, [r4, #0x19]
    mov     r1, r5
    bl      func_020357f4
    cmp     r0, #0
    ble     _L4c
    mov     r0, #0
    str     r0, [r4, #0x14]
    sub     r0, r0, #2
    ldmfd   sp!, {r3, r4, r5, pc}
_L4c:
    add     r5, r5, #1
    cmp     r5, #0xf
    blt     _L28
_L58:
    ldrsb   r1, [r4, #0x10]
    mvn     r0, #1
    cmp     r1, r0
    beq     _L150
    ldr     r2, [r4, #0x14]
    ldr     r1, =0x5fa0
    cmp     r2, r1
    addlt   r1, r2, #0x88
    strlt   r1, [r4, #0x14]
    ldmltfd sp!, {r3, r4, r5, pc}
    mov     r5, #0
_L84:
    ldrsb   r0, [r4, #0x19]
    mov     r1, r5
    strb    r0, [r4, #0x10]
    ldrsb   r0, [r4, #0x19]
    bl      func_020357f4
    cmp     r0, #0
    ble     _Lb0
    mov     r0, #0
    str     r0, [r4, #0x14]
    sub     r0, r0, #2
    ldmfd   sp!, {r3, r4, r5, pc}
_Lb0:
    add     r5, r5, #1
    cmp     r5, #0xf
    blt     _L84
    ldr     r0, [r4, #0xc]
    cmp     r0, #0
    ble     _L120
    mov     r0, #1
    sub     r1, r0, #2
    bl      func_ov002_0206f6e4
    strb    r0, [r4, #0x11]
    ldrsb   r0, [r4, #0x11]
    cmp     r0, #0
    mvnlt   r0, #1
    ldmltfd sp!, {r3, r4, r5, pc}
    ldr     r1, =func_ov002_0206f04c
    mvn     r0, #0
    cmp     r1, r0
    strne   r1, [r4]
    mov     r1, #0
    sub     r0, r1, #1
    cmp     r1, r0
    mvn     r0, #0
    strne   r1, [r4, #4]
    cmp     r1, r0
    movne   r0, #0
    strne   r0, [r4, #8]
    mvn     r0, #1
    ldmfd   sp!, {r3, r4, r5, pc}
_L120:
    ldr     r1, =func_ov002_0206f0c8
    mvn     r0, #0
    cmp     r1, r0
    strne   r1, [r4]
    mov     r1, #0
    sub     r0, r1, #1
    cmp     r1, r0
    mvn     r0, #0
    strne   r1, [r4, #4]
    cmp     r1, r0
    movne   r0, #0
    strne   r0, [r4, #8]
_L150:
    ldrsb   r0, [r4, #0x10]
    ldmfd   sp!, {r3, r4, r5, pc}
}
