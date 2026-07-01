extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_ov022_02091228(void);

asm void func_ov052_020b6e18(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    ldr     r0, [pc, #0x18]
    ldr     r0, [r4, r0]
_L_0008:
    bl      func_ov022_02091228
    ldr     r0, [pc, #0x10]
    ldr     r0, [r4, r0]
    add     r0, #0x30
_L_0012:
    bl      func_ov022_02091228
    ldr     r0, [pc, #8]
    ldr     r0, [r4, r0]
_L_001a:
    bl      NNSi_FndFreeFromDefaultHeap
    pop     {r4, pc}
    mov     r6, #0x44
    lsl     r0, r0, #0
}
