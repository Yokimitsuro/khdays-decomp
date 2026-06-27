extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov042_020b3db8(void);
extern void func_ov022_0209fab4(void);
extern void *data_ov042_020b4800;

asm void func_ov042_020b325c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    bl      func_ov042_020b3db8
    mov     r0, r4
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov042_020b4800
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
}
