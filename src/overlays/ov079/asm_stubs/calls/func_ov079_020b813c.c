extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov079_020b9a00[];
extern void func_ov022_0209fab4(void);
extern void func_ov079_020b8848(void);

asm void func_ov079_020b813c(void)
{
    push    {r4, lr}
_L_0002:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
_L_0008:
    bl      func_ov079_020b8848
    add     r0, r4, #0
_L_000e:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #8]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_ov079_020b9a00
}
