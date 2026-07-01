extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov058_020b663c(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void data_ov058_020b7e00(void);

asm void func_ov058_020b5a5c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    bl      func_ov058_020b663c
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
    dcd     data_ov058_020b7e00
}
