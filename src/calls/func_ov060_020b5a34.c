extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov060_020b5a90(void);
extern void func_ov060_020b5f6c(void);

asm void func_ov060_020b5a34(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
_L_000c:
    bl      func_ov060_020b5a90
    add     r0, r4, #0
_L_0012:
    bl      func_ov060_020b5f6c
    add     r0, r4, #0
    mov     r1, #0x54
    mov     r2, #0xd7
_L_001c:
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
