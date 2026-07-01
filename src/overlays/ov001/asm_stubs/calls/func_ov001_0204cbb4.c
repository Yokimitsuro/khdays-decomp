extern void func_020163cc(void);
extern void G3X_InitMtxStack(void);
extern void GX_SetBankForTex(int);
extern void GX_BeginLoadOBJExtPltt(int);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForBGExtPltt(int);
extern void func_020056b4(int, int, int);
extern void func_ov001_0204cb30(void);
extern void func_0200566c(void);

asm void func_ov001_0204cbb4(void)
{
    stmdb sp!, {r4, lr}
    bl    func_020163cc
    bl    G3X_InitMtxStack
    mov   r0, #7
    bl    GX_SetBankForTex
    mov   r0, #0x60
    bl    GX_BeginLoadOBJExtPltt
    mov   r0, #0x10
    bl    GX_SetBankForBG
    mov   r0, #0
    bl    GX_SetBankForBGExtPltt
    mov   r0, #1
    mov   r1, #0
    mov   r2, r0
    bl    func_020056b4
    mov   r0, #0x4000000
    ldr   r2, [r0]
    ldr   r1, =0xffffcffd
    bic   r2, r2, #0x1f00
    orr   r2, r2, #0x300
    str   r2, [r0]
    ldr   r2, [r0]
    mov   lr, #0
    bic   r2, r2, #0x7000000
    str   r2, [r0]
    ldr   r2, [r0]
    mov   ip, #2
    bic   r2, r2, #0x38000000
    str   r2, [r0]
    ldrh  r4, [r0, #0xa]
    ldr   r2, =0x0000cffb
    ldr   r3, =0xbfff0000
    and   r4, r4, #0x43
    orr   r4, r4, #0x400
    strh  r4, [r0, #0xa]
    ldrh  r4, [r0, #8]
    bic   r4, r4, #3
    orr   r4, r4, #1
    strh  r4, [r0, #8]
    ldrh  r4, [r0, #0xa]
    bic   r4, r4, #3
    strh  r4, [r0, #0xa]
    ldrh  r4, [r0, #0x60]
    and   r1, r4, r1
    strh  r1, [r0, #0x60]
    ldrh  r1, [r0, #0x60]
    bic   r1, r1, #0x3000
    orr   r1, r1, #0x10
    strh  r1, [r0, #0x60]
    strh  lr, [r0, #0x50]
    str   ip, [r0, #0x540]
    ldrh  r1, [r0, #0x60]
    and   r1, r1, r2
    strh  r1, [r0, #0x60]
    ldrh  r1, [r0, #0x60]
    bic   r1, r1, #0x3000
    orr   r1, r1, #8
    strh  r1, [r0, #0x60]
    str   r3, [r0, #0x580]
    bl    func_ov001_0204cb30
    bl    func_0200566c
    ldr   r1, =0x04001000
    ldr   r0, [r1]
    orr   r0, r0, #0x10000
    str   r0, [r1]
    ldmia sp!, {r4, pc}
}
