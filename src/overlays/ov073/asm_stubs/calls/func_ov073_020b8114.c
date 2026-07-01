extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov073_020b818c(void);
extern void func_ov073_020b9f94(void);

asm void func_ov073_020b8114(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
_L_0004:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x20]
    mov     r1, #0
    str     r1, [r4, r0]
    add     r0, r5, #0
_L_0012:
    bl      func_ov073_020b818c
    add     r0, r4, #0
    mov     r1, #0x45
    mov     r2, #0xc6
_L_001c:
    bl      func_ov022_020a4798
    add     r0, r4, #0
_L_0022:
    bl      func_ov073_020b9f94
    ldr     r0, [pc, #8]
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    cmp     r6, #0x1c
    lsl     r0, r0, #0
    dcd     func_ov022_0209fb24
}
