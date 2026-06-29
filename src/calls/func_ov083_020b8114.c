extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov083_020b8178(void);
extern void func_ov083_020b9010(void);

asm void func_ov083_020b8114(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
    bl      func_ov083_020b8178
    add     r0, r4, #0
    bl      func_ov083_020b9010
    add     r0, r4, #0
    mov     r1, #0x4a
    mov     r2, #0xc9
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
