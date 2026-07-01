extern void func_ov002_020519b0(void);
extern void func_ov022_02095524(void);
extern void func_ov022_02095600(void);
extern void func_ov022_020a384c(void);
extern void func_ov022_020a3c78(void);
extern void func_ov022_020a46f8(void);
extern void func_ov066_020b60f0(void);
extern void func_ov066_020b6340(void);

asm void func_ov066_020b5ccc(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r8, r0
    mov     r7, r1
    add     r1, r8, #0xc50
    cmp     r7, #0x2e
    add     r4, r1, #0x2000
    mvn     r5, #0
    mov     r6, #0
    bgt     _L004c
    cmp     r7, #0x2e
    bge     _L0060
    cmp     r7, #4
    bgt     _L0110
    cmp     r7, #0
    blt     _L0110
    cmpne   r7, #1
    cmpne   r7, #4
    beq     _L0090
    b       _L0110
_L004c:
    cmp     r7, #0x30
    ble     _L0110
    cmp     r7, #0x31
    beq     _L0078
    b       _L0110
_L0060:
    ldr     r1, [r8, #0x6bc]
    cmp     r1, r7
    beq     _L0110
    str     r6, [r4, #0xc]
    bl      func_ov066_020b6340
    b       _L0110
_L0078:
    ldr     r0, [r8, #0x6bc]
    cmp     r0, r7
    beq     _L0110
    mov     r0, r4
    bl      func_ov066_020b60f0
    b       _L0110
_L0090:
    add     r0, r8, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    beq     _L00dc
    ldr     r1, [r8, #0x6bc]
    cmp     r7, r1
    bne     _L00bc
    ldr     r0, [r4, #0xc]
    cmp     r0, #0
    bne     _L0110
_L00bc:
    ldr     r2, [r8, #0xc]
    mov     r0, r7
    mov     r5, #1
    bl      func_ov002_020519b0
    mov     r6, r0
    cmp     r7, #4
    moveq   r6, #5
    b       _L0110
_L00dc:
    ldr     r0, [r8, #0x6bc]
    ldr     r2, [r8, #0x20]
    cmp     r7, r0
    bne     _L0110
    ldrh    r0, [r2, #4]
    tst     r0, #4
    bne     _L0110
    ldr     r1, [r2, #0xf4]
    ldr     r0, [r2, #0x10]
    ldr     r1, [r1, r7, lsl #2]
    cmp     r1, r0
    movne   r0, #0x2f
    strne   r0, [r8, #0x6bc]
_L0110:
    cmp     r5, #0
    blt     _L0154
    mov     r2, #1
    mov     r0, r8
    mov     r1, r7
    str     r2, [r4, #0xc]
    bl      func_ov022_020a46f8
    add     r0, r8, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095600
    mov     r1, r0
    mov     r0, r8
    mov     r2, r5
    mov     r3, r6
    bl      func_ov022_020a3c78
    str     r7, [r8, #0x6bc]
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
_L0154:
    mov     r0, r8
    mov     r1, r7
    bl      func_ov022_020a384c
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
