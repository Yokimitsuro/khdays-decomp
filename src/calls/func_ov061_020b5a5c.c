extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov061_020b65b8(void);
extern void func_ov022_0209fab4(void *arg);
extern int data_ov061_020b7000;

asm void func_ov061_020b5a5c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov061_020b65b8
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov061_020b7000
    mov     r1, #0
    str     r1, [r0]
    pop     {r4, pc}
}
