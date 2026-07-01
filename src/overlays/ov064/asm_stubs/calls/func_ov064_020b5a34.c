extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov064_020b5a98(void *arg);
extern void func_ov064_020b6930(void *arg);
extern void func_ov022_020a4798(void *arg, int x, int y);
extern void func_ov022_0209fb24(void);

asm void *func_ov064_020b5a34(void *arg)
{
    push    {r3, r4, r5, lr}
    mov     r5, r0
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    mov     r0, r5
    bl      func_ov064_020b5a98
    mov     r0, r4
    bl      func_ov064_020b6930
    mov     r0, r4
    mov     r1, #0x4a
    mov     r2, #0xc9
    bl      func_ov022_020a4798
    ldr     r0, =func_ov022_0209fb24
    pop     {r3, r4, r5, pc}
}
