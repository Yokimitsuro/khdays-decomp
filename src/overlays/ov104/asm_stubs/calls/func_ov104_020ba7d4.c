extern char data_0204c240[];
extern char data_ov104_020bc1fc[];
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0201ef9c(void);
extern void func_0202a3cc(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov104_020ba89c(void);
extern void func_ov104_020baffc(void);

asm void func_ov104_020ba7d4(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x4c]
    mov     r1, #0
    str     r1, [r4, r0]
    add     r0, r5, #0
    bl      func_ov104_020ba89c
    ldr     r0, [pc, #0x44]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_0042
    ldr     r1, [r5, #0]
    ldr     r0, [pc, #0x3c]
    add     r1, r1, #7
    bl      func_0201ef9c
    ldr     r2, [pc, #0x2c]
    str     r0, [r4, r2]
    add     r0, r2, #0
    ldr     r1, [r4, #0x20]
    ldr     r3, [r5, #0]
    sub     r0, #0x24
    ldr     r2, [r4, r2]
    add     r0, r4, r0
    add     r1, r1, #4
    add     r3, r3, #7
    bl      func_0202a3cc
_L_0042:
    add     r0, r4, #0
    bl      func_ov104_020baffc
    add     r0, r4, #0
    mov     r1, #0x51
    mov     r2, #0xd2
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0x10]
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    cmp     r4, #0x50
    lsl     r0, r0, #0
    dcd     data_0204c240
    dcd     data_ov104_020bc1fc
    dcd     func_ov022_0209fb24
}
