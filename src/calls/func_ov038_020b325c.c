extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov038_020b3930(void);
extern void func_ov022_0209fab4(void);
extern void data_ov038_020b4ca0(void);

asm void func_ov038_020b325c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov038_020b3930
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #8]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_ov038_020b4ca0
}
