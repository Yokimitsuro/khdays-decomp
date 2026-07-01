extern void func_0201e374(int);
extern void func_0201e3cc(int);
extern void func_0201e1d0(void);
extern void func_020056b4(int, int, int);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForBGExtPltt(int);
extern void GX_SetBankForOBJ(int);

asm void func_ov007_0204cac0(void)
{
    stmfd   sp!, {r3, lr}
    mvn     r0, #0xf
    bl      func_0201e374
    mvn     r0, #0xf
    bl      func_0201e3cc
    bl      func_0201e1d0
    mov     r0, #1
    mov     r2, r0
    mov     r1, #0
    bl      func_020056b4
    mov     r0, #1
    bl      GX_SetBankForBG
    mov     r0, #0x20
    bl      GX_SetBankForBGExtPltt
    mov     r0, #2
    bl      GX_SetBankForOBJ
    mov     r0, #0x4000000
    ldr     r3, [r0]
    ldr     r1, =0xffcfffef
    add     r2, r0, #0x304
    and     r1, r3, r1
    orr     r1, r1, #0x10
    orr     r1, r1, #0x200000
    str     r1, [r0]
    ldrh    r1, [r0, #0xa]
    and     r1, r1, #0x43
    orr     r1, r1, #0x90
    strh    r1, [r0, #0xa]
    ldrh    r1, [r0, #0xc]
    and     r1, r1, #0x43
    orr     r1, r1, #0x104
    strh    r1, [r0, #0xc]
    ldrh    r1, [r2]
    orr     r1, r1, #0x8000
    strh    r1, [r2]
    ldr     r1, [r0]
    bic     r1, r1, #0x1f00
    orr     r1, r1, #0x1600
    str     r1, [r0]
    ldrh    r1, [r0, #0xa]
    bic     r1, r1, #3
    orr     r1, r1, #1
    strh    r1, [r0, #0xa]
    ldrh    r1, [r0, #0xc]
    bic     r1, r1, #3
    strh    r1, [r0, #0xc]
    ldmfd   sp!, {r3, pc}
}
