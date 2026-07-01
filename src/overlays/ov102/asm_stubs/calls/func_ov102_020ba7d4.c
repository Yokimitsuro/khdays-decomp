extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov102_020ba81c(void);
extern void func_ov102_020bae04(void);
extern void func_ov022_020a4798(void);
extern void func_ov022_0209fb24(void);

asm void func_ov102_020ba7d4(void *arg)
{
    push    {r3, r4, r5, lr}
    mov     r5, r0
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    mov     r0, r5
    bl      func_ov102_020ba81c
    mov     r0, r4
    bl      func_ov102_020bae04
    mov     r0, r4
    mov     r1, #0x52
    mov     r2, #0xd4
    bl      func_ov022_020a4798
    ldr     r0, =func_ov022_0209fb24
    pop     {r3, r4, r5, pc}
}
