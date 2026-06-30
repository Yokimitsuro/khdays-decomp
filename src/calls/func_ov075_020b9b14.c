extern void func_ov022_02091228(void);
extern void NNSi_FndFreeFromDefaultHeap(void);

asm void func_ov075_020b9b14(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    ldr     r0, [pc, #0x10]
    ldr     r0, [r4, r0]
    bl      func_ov022_02091228
    ldr     r0, [pc, #8]
    ldr     r0, [r4, r0]
    bl      NNSi_FndFreeFromDefaultHeap
    pop     {r4, pc}
    mov     r8, r8
    mov     r6, #0x44
    lsl     r0, r0, #0
}
