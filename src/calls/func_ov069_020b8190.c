extern void func_0201ef9c(void);
extern void func_ov069_020b815c(void);
extern void func_020235d0(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void data_ov069_020baa20(void);
extern void data_ov069_020baa70(void);

asm void func_ov069_020b8190(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    cmp     r0, #3
    blo     _L_000a
    mov     r0, #0
    pop     {r3, r4, r5, r6, r7, pc}
_L_000a:
    lsl     r1, r0, #2
    ldr     r0, [pc, #0x50]
    ldr     r5, [r0, r1]
    ldr     r0, [pc, #0x50]
    mov     r1, #0xe
    bl      func_0201ef9c
    add     r4, r0, #0
    beq     _L_005a
    mov     r0, #0
    ldrsh   r1, [r5, r0]
    cmp     r1, #0
    ble     _L_0054
    ldr     r6, [pc, #0x40]
    add     r7, r0, #0
_L_0028:
    add     r0, r4, #0
    bl      func_ov069_020b815c
    lsl     r1, r0, #1
    add     r0, r0, r1
    add     r0, r0, r6
    mov     r1, #3
    bl      func_020235d0
    cmp     r0, #2
    blo     _L_0042
    mov     r0, #1
    b       _L_0044
_L_0042:
    mov     r0, #0
_L_0044:
    cmp     r0, #0
    bne     _L_004c
    mov     r0, #0
    pop     {r3, r4, r5, r6, r7, pc}
_L_004c:
    add     r5, r5, #2
    ldrsh   r1, [r5, r7]
    cmp     r1, #0
    bgt     _L_0028
_L_0054:
    add     r0, r4, #0
    bl      NNSi_FndFreeFromDefaultHeap
_L_005a:
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     data_ov069_020baa20
    dcd     data_ov069_020baa70
    cmp     r0, #0xe4
    lsl     r0, r0, #0
}
