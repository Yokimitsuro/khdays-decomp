extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov035_020b4ca0[];
extern void func_02020a9c(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void func_ov035_020b3adc(void);

asm void func_ov035_020b3264(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x28]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
_L_0012:
    bl      func_ov002_02051fc8
_L_0016:
    bl      func_02020a9c
    cmp     r0, #0x2a
    beq     _L_0024
    add     r0, r4, #0
_L_0020:
    bl      func_ov035_020b3adc
_L_0024:
    add     r0, r4, #0
_L_0026:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #0xc]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    cmp     r4, #0x50
    lsl     r0, r0, #0
    dcd     data_ov035_020b4ca0
}
