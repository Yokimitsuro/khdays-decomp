extern void NNSi_FndFreeFromDefaultHeap(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_0204c240[];
extern char data_ov044_020b5620[];
extern void func_0202a440(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void func_ov044_020b4868(void);

asm void func_ov044_020b32b4(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x3c]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_0022
    ldr     r0, [pc, #0x38]
    add     r0, r4, r0
_L_0016:
    bl      func_0202a440
    ldr     r0, [pc, #0x34]
    ldr     r0, [r4, r0]
_L_001e:
    bl      NNSi_FndFreeFromDefaultHeap
_L_0022:
    ldr     r0, [pc, #0x30]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
_L_002c:
    bl      func_ov002_02051fc8
    ldr     r0, [pc, #0x24]
    add     r0, r4, r0
_L_0034:
    bl      func_ov044_020b4868
    add     r0, r4, #0
_L_003a:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #0x1c]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_0204c240
    dcd     0x00002c2c
    dcd     0x00002c50
    dcd     0x00002c54
    dcd     0x00002ca8
    dcd     data_ov044_020b5620
}
