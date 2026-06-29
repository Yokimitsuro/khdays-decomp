extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov056_020b7620[];
extern void func_ov022_0209fab4(void);
extern void func_ov056_020b61ec(void);
extern void func_ov056_020b6444(void);

asm void func_ov056_020b5a5c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov056_020b61ec
    add     r0, r4, #0
_L_000e:
    bl      func_ov056_020b6444
    add     r0, r4, #0
_L_0014:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #4]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    dcd     data_ov056_020b7620
}
