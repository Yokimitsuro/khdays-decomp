extern void G2_GetBG3ScrPtr(void);
extern void GX_LoadBGPltt(void);
extern void GX_SetBankForBG(void);
extern void GX_SetBankForOBJ(void);
extern void GX_SetBankForSubBG(void);
extern void GX_SetBankForSubOBJ(void);
extern void MIi_CpuClearFast(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern void OS_IsThreadAvailable_0x02023650(void);
extern int data_ov010_0204cf88;
extern int data_ov010_0204cfb4;
extern int data_ov010_0204cfc8;
extern void func_0201e1d0(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_0202362c(void);
extern void func_02023c30(void);
extern void func_0202f7fc(void);
extern void func_0202f834(void);
extern void func_ov010_0204cac0(void);
extern void func_ov010_0204cb04(void);
extern void func_ov010_0204ce60(void);

asm void func_ov010_0204cb3c(void)
{
    stmfd   sp!, {r4, r5, r6, r7, lr}
    sub     sp, sp, #0x14
    mov     r6, r0
    bl      NNSi_FndGetCurrentRootHeap
    ldr     r1, =data_ov010_0204cf88
    mov     r4, r0
    ldrh    r0, [r1, #2]
    ldrh    r1, [r1]
    strh    r0, [sp, #2]
    strh    r1, [sp]
    bl      OS_IsThreadAvailable_0x02023650
    mov     r5, r0
    mov     r0, #0
    bl      func_0202362c
    mov     r0, #0x5000000
    mov     r1, #0
    mov     r2, #0x4000000
    strh    r1, [r0]
    add     r0, r0, #0x400
    strh    r1, [r0]
    ldr     r0, [r2]
    add     r1, r2, #0x1000
    bic     r0, r0, #0x1f00
    str     r0, [r2]
    ldr     r0, [r1]
    bic     r0, r0, #0x1f00
    str     r0, [r1]
    bl      func_0201e1d0
    mov     r0, #0
    bl      func_02023c30
    ldr     r3, =0x04000304
    mov     r2, #0x4000000
    ldrh    r1, [r3]
    mov     r0, #3
    orr     r1, r1, #0x8000
    strh    r1, [r3]
    ldr     r1, [r2]
    bic     r1, r1, #0x38000000
    str     r1, [r2]
    ldr     r1, [r2]
    bic     r1, r1, #0x7000000
    str     r1, [r2]
    bl      GX_SetBankForBG
    mov     r0, #4
    bl      GX_SetBankForSubBG
    mov     r0, #0x70
    bl      GX_SetBankForOBJ
    mov     r0, #8
    bl      GX_SetBankForSubOBJ
    ldr     r1, =0x04000008
    ldrh    r0, [r1]
    bic     r0, r0, #3
    orr     r0, r0, #3
    strh    r0, [r1]
    ldrh    r0, [r1, #2]
    bic     r0, r0, #3
    orr     r0, r0, #2
    strh    r0, [r1, #2]
    ldrh    r0, [r1, #4]
    bic     r0, r0, #3
    orr     r0, r0, #1
    strh    r0, [r1, #4]
    ldrh    r0, [r1, #6]
    bic     r0, r0, #3
    strh    r0, [r1, #6]
    add     r1, r1, #0x2fc
    ldrh    r0, [r1]
    orr     r0, r0, #0x8000
    strh    r0, [r1]
    bl      G2_GetBG3ScrPtr
    mov     r1, r0
    mov     r0, #0
    mov     r2, #0x600
    bl      MIi_CpuClearFast
    ldr     r7, =0x0400000e
    add     r0, sp, #0
    ldrh    r3, [r7]
    mov     r1, #0
    mov     r2, #4
    and     r3, r3, #0x43
    orr     r3, r3, #0x304
    strh    r3, [r7]
    bl      GX_LoadBGPltt
    ldr     r1, =data_ov010_0204cfb4
    mov     r0, r4
    bl      func_ov010_0204cac0
    mvn     r0, #0
    cmp     r6, r0
    mov     r0, r4
    bne     _L174
    mov     r1, #1
    bl      func_ov010_0204cb04
    b       _L17c
_L174:
    mov     r1, #0
    bl      func_ov010_0204cb04
_L17c:
    ldr     r1, =data_ov010_0204cfc8
    str     r0, [r4, #0x74]
    add     r0, r4, #0xc
    bl      func_0202f7fc
    mov     r7, #0
    mov     r1, #0x20
    mov     lr, #0x18
    mov     ip, #6
    strh    r1, [sp, #8]
    add     r3, sp, #4
    add     r0, r4, #0x18
    add     r2, r4, #0xc
    mov     r1, #3
    strh    lr, [sp, #0xa]
    strh    r7, [sp, #4]
    strh    r7, [sp, #6]
    strh    r7, [sp, #0xc]
    strh    r7, [sp, #0x10]
    strh    ip, [sp, #0x12]
    strh    r7, [sp, #0xe]
    bl      func_0202f834
    mov     r1, #0x4000000
    ldr     r0, [r1]
    add     r2, r1, #0x1000
    bic     r0, r0, #0x1f00
    orr     r0, r0, #0x800
    str     r0, [r1]
    ldr     r1, [r2]
    mov     r0, r7
    bic     r1, r1, #0x1f00
    orr     r1, r1, #0x800
    str     r1, [r2]
    bl      func_0201e374
    mov     r0, r7
    bl      func_0201e3cc
    mov     r0, #2
    str     r0, [r4, #0x78]
    mov     r0, r5
    str     r6, [r4, #0x7c]
    bl      func_0202362c
    ldr     r0, =func_ov010_0204ce60
    add     sp, sp, #0x14
    ldmfd   sp!, {r4, r5, r6, r7, pc}
}
