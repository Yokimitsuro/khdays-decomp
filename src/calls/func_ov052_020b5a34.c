extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov052_020b8008[];
extern void func_0202a388(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov052_020b5ad8(void);
extern void func_ov052_020b7194(void);

asm void func_ov052_020b5a34(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
_L_0004:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r1, [pc, #0x3c]
    mov     r0, #1
    ldrb    r2, [r4, r1]
    bic     r2, r0
    strb    r2, [r4, r1]
    ldrb    r2, [r4, r1]
    mov     r0, #4
    bic     r2, r0
    strb    r2, [r4, r1]
    add     r0, r5, #0
_L_001e:
    bl      func_ov052_020b5ad8
    ldr     r0, [pc, #0x28]
    ldr     r1, [r4, #0x20]
    ldr     r3, [r5, #0]
    ldr     r2, [pc, #0x24]
    add     r0, r4, r0
    add     r1, r1, #4
    add     r3, r3, #7
_L_0030:
    bl      func_0202a388
    add     r0, r4, #0
    mov     r1, #0x43
    mov     r2, #0xc5
_L_003a:
    bl      func_ov022_020a4798
    add     r0, r4, #0
_L_0040:
    bl      func_ov052_020b7194
    ldr     r0, [pc, #0xc]
    pop     {r3, r4, r5, pc}
    cmp     r4, #0x30
    lsl     r0, r0, #0
    cmp     r6, #0x44
    lsl     r0, r0, #0
    dcd     data_ov052_020b8008
    dcd     func_ov022_0209fb24
}
