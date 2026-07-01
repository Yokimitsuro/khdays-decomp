extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov095_020bb3dc(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void data_ov095_020bcba0(void);

asm void func_ov095_020ba7fc(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov095_020bb3dc
    ldr     r0, [pc, #0x28]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    mov     r0, #0xb2
    mov     r1, #0x91
    lsl     r0, r0, #6
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #8]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    dcd     data_ov095_020bcba0
}
