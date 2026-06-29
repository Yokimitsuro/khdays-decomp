extern void NNSi_FndGetCurrentRootHeap(void);
extern void WM_EndKeySharing_0x02023ad0(void);
extern void func_0202a440(void);
extern void func_0202a7dc(void);
extern void func_ov022_0209fab4(void);
extern void func_ov032_020b4618(void);
extern void func_ov032_020b49f8(void);

asm void func_ov032_020b328c(void)
{
    push    {r4, lr}
_L_0002:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
_L_0008:
    bl      func_ov032_020b4618
    add     r0, r4, #0
_L_000e:
    bl      func_ov032_020b49f8
    ldr     r0, [pc, #0x28]
    ldr     r0, [r4, r0]
_L_0016:
    bl      WM_EndKeySharing_0x02023ad0
    ldr     r0, [pc, #0x24]
    add     r0, r4, r0
_L_001e:
    bl      func_0202a7dc
    ldr     r0, [pc, #0x20]
    add     r0, r4, r0
_L_0026:
    bl      func_0202a7dc
    ldr     r0, [pc, #0x1c]
    add     r0, r4, r0
_L_002e:
    bl      func_0202a440
    add     r0, r4, #0
_L_0034:
    bl      func_ov022_0209fab4
    pop     {r4, pc}
    mov     r8, r8
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    cmp     r4, #0x34
    lsl     r0, r0, #0
    cmp     r5, #0x3c
    lsl     r0, r0, #0
    cmp     r6, #0x44
    lsl     r0, r0, #0
}
