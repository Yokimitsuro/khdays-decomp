extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov093_020ba820(void);
extern void func_ov093_020bb138(void);

asm void func_ov093_020ba7d4(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
_L_000c:
    bl      func_ov093_020ba820
    add     r0, r4, #0
_L_0012:
    bl      func_ov093_020bb138
    add     r0, r4, #0
    mov     r1, #0x46
    mov     r2, #0xcf
_L_001c:
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
