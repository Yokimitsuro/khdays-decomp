extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov095_020ba83c(void);
extern void func_ov095_020bb2d0(void);
extern void func_ov022_020a4798(void);
extern void func_ov022_0209fb24(void);

asm void func_ov095_020ba7d4(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
    bl      func_ov095_020ba83c
    add     r0, r4, #0
    bl      func_ov095_020bb2d0
    add     r0, r4, #0
    mov     r1, #0x4d
    mov     r2, #0xcd
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
