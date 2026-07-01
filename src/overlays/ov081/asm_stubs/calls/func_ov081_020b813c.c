extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov081_020b8c98(void);
extern void func_ov022_0209fab4(void *arg);
extern int data_ov081_020b96e0;

asm void func_ov081_020b813c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov081_020b8c98
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov081_020b96e0
    mov     r1, #0
    str     r1, [r0]
    pop     {r4, pc}
}
