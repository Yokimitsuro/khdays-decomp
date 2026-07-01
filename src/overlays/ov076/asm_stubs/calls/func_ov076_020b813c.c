extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov076_020b9d00[];
extern void func_ov022_0209fab4(void);
extern void func_ov076_020b88cc(void);
extern void func_ov076_020b8b24(void);

asm void func_ov076_020b813c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov076_020b88cc
    add     r0, r4, #0
_L_000e:
    bl      func_ov076_020b8b24
    add     r0, r4, #0
_L_0014:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #4]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    dcd     data_ov076_020b9d00
}
