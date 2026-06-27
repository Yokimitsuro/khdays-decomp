extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov081_020b815c(void *arg);
extern void func_ov081_020b8c14(void *arg);
extern void func_ov022_020a4798(void *arg, int x, int y);
extern void func_ov022_0209fb24(void);

asm void func_ov081_020b8114(void *arg)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
    bl      func_ov081_020b815c
    add     r0, r4, #0
    mov     r1, #0x4e
    mov     r2, #0xc7
    bl      func_ov022_020a4798
    add     r0, r4, #0
    bl      func_ov081_020b8c14
    ldr     r0, =func_ov022_0209fb24
    pop     {r3, r4, r5, pc}
}
