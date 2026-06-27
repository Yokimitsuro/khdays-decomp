extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov042_020b327c(void);
extern void func_ov022_020a4798(void);
extern void func_ov042_020b3d34(void);
extern void func_ov022_0209fb24(void);

asm void *func_ov042_020b3234(void)
{
    push    {r3, r4, r5, lr}
    mov     r5, r0
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    mov     r0, r5
    bl      func_ov042_020b327c
    mov     r0, r4
    mov     r1, #0x4e
    mov     r2, #0xc7
    bl      func_ov022_020a4798
    mov     r0, r4
    bl      func_ov042_020b3d34
    ldr     r0, =func_ov022_0209fb24
    pop     {r3, r4, r5, pc}
}
