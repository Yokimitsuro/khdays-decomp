extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov102_020bae54(void);
extern void func_ov022_0209fab4(void);
extern char data_ov102_020bb920[];

asm void func_ov102_020ba7fc(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    bl      func_ov102_020bae54
    mov     r0, r4
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov102_020bb920
    mov     r1, #0
    str     r1, [r0]
    pop     {r4, pc}
}
