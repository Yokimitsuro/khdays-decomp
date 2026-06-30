extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov075_020b989c(void);
extern void func_ov002_02051fc8(void);
extern void func_ov075_020b87c4(void);
extern void func_ov075_020b9b14(void);
extern void func_ov022_0209fab4(void);
extern void data_ov075_020b9e20(void);

asm void func_ov075_020b8148(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov075_020b989c
    ldr     r0, [pc, #0x24]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    add     r0, r4, #0
    bl      func_ov075_020b87c4
    add     r0, r4, #0
    bl      func_ov075_020b9b14
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #8]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    dcd     data_ov075_020b9e20
}
