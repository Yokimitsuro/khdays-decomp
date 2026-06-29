extern char data_0204c240[];
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a440(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void func_ov104_020bb08c(void);

asm void func_ov104_020ba83c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x40]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_0022
    ldr     r0, [pc, #0x3c]
    add     r0, r4, r0
    bl      func_0202a440
    ldr     r0, [pc, #0x38]
    ldr     r0, [r4, r0]
    bl      NNSi_FndFreeFromDefaultHeap
_L_0022:
    ldr     r0, [pc, #0x34]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    ldr     r0, [pc, #0x28]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    add     r0, r4, #0
    bl      func_ov104_020bb08c
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    pop     {r4, pc}
    dcd     data_0204c240
    dcd     0x00002c2c
    dcd     0x00002c50
    dcd     0x00002c54
    dcd     0x00002ca8
}
