extern char data_ov083_020b9b00[];
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(void);
extern void func_ov022_0209fab4(void);
extern void func_ov083_020b9058(void);

asm void func_ov083_020b813c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x28]
    ldr     r1, [r4, r0]
    cmp     r1, #0
    beq     _L_001e
    add     r0, r0, #4
    add     r0, r4, r0
    bl      func_0202a7dc
    ldr     r0, [pc, #0x18]
    mov     r1, #0
    str     r1, [r4, r0]
_L_001e:
    add     r0, r4, #0
    bl      func_ov083_020b9058
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #0xc]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    dcd     data_ov083_020b9b00
}
