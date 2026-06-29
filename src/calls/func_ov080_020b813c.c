extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov080_020b9be0[];
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void func_ov080_020b8720(void);

asm void func_ov080_020b813c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x20]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
_L_0012:
    bl      func_ov002_02051fc8
    add     r0, r4, #0
_L_0018:
    bl      func_ov080_020b8720
    add     r0, r4, #0
_L_001e:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #0xc]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    cmp     r4, #0x30
    lsl     r0, r0, #0
    dcd     data_ov080_020b9be0
}
