extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_02024ee8(void);
extern void func_ov007_0204d33c(void);
extern void func_020235d0(void);
extern void func_ov007_0204d374(void);
extern void func_ov007_0204cac0(void);
extern void func_0201ef9c(void);
extern void func_02024c94(void);
extern void GFXi_EnqueueCommand(void);
extern void func_02024ae0(void);
extern void func_02024b04(void);
extern void func_02032388(void);
extern void WM_EndKeySharing_0x02032444(void);
extern void func_0203257c(void);
extern void func_0203281c(void);
extern void func_0202f7fc(void);
extern void func_0202f834(void);
extern void GX_LoadBGPltt(void);
extern char data_ov007_0204d420[];
extern char data_ov007_0204d3d8[];
extern char data_ov007_0204d3e4[];
extern char data_ov007_0204d3f8[];
extern char data_ov007_0204d3ac[];
extern void func_ov007_0204cf18(void);

asm void func_ov007_0204cb80(void *r0)
{
    stmfd   sp!, {r4, r5, r6, r7, lr}
    sub     sp, sp, #0x2c
    mov     r5, r0
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r1, [pc, #0x278]
    ldr     r0, [pc, #0x278]
    str     r4, [r1]
    add     r2, r4, #0x5000
    mov     r1, #0xf
    str     r5, [r2, #0xac0]
    bl      func_02024ee8
    str     r0, [r4]
    ldr     r1, [pc, #0x260]
    add     r0, r4, #8
    bl      func_ov007_0204d33c
    mov     r0, #0
    mov     r1, #9
    bl      func_020235d0
    add     r1, r4, #0x5000
    str     r0, [r1, #0xab8]
    cmp     r0, #0xd
    addls   pc, pc, r0, lsl #2
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_def
    b       _L_c8
    b       _L_c9
    b       _L_ca
    b       _L_cb
    b       _L_cc
    b       _L_cd
    b       _L_ce
_L_c8:
    mov     r1, #1
    b       _L_after
_L_c9:
    mov     r1, #2
    b       _L_after
_L_ca:
    mov     r1, #3
    b       _L_after
_L_cb:
    mov     r1, #4
    b       _L_after
_L_cc:
    mov     r1, #5
    b       _L_after
_L_cd:
    mov     r1, #6
    b       _L_after
_L_ce:
    mov     r1, #7
    b       _L_after
_L_def:
    mov     r1, #0
_L_after:
    add     r0, r4, #8
    bl      func_ov007_0204d374
    str     r0, [r4, #0x74]
    mov     r1, #0
    str     r1, [r4, #0x78]
    add     r0, r4, #0x5000
    str     r1, [r0, #0xabc]
    bl      func_ov007_0204cac0
    ldr     r1, [r4]
    ldr     r0, [pc, #0x1a0]
    add     r1, r1, #0x8000
    and     r0, r1, r0
    mov     r0, r0, lsl #7
    orr     r0, r0, #0x80000000
    mov     r1, #0xe
    bl      func_0201ef9c
    str     r0, [r4, #4]
    add     r0, r4, #0x5000
    ldr     r2, [r0, #0xabc]
    add     r0, r4, #0x14
    str     r2, [sp]
    ldr     r1, [r4, #4]
    mov     r3, r2
    bl      func_02024c94
    ldr     r3, [r4, #0x1c]
    mov     r0, #0x11
    ldr     r2, [r3, #0xc]
    ldr     r3, [r3, #8]
    mov     r1, #0x2000
    bl      GFXi_EnqueueCommand
    ldr     r1, [r4, #0x18]
    mov     r0, #1
    ldr     r3, [r1, #0x10]
    mov     r2, #0
    bl      func_02024ae0
    ldr     r1, [r4, #0x14]
    mov     r0, #1
    ldr     r3, [r1, #8]
    mov     r2, #0
    bl      func_02024b04
    ldr     r1, [r4]
    ldr     r0, [pc, #0x120]
    add     r1, r1, #0x8000
    and     r0, r1, r0
    mov     r0, r0, lsl #7
    orr     r0, r0, #0x80000001
    str     r0, [sp, #0x1c]
    mov     r0, #1
    str     r0, [sp, #0x20]
    mov     r0, #0
    str     r0, [sp, #0x24]
    str     r0, [sp, #0x28]
    add     r0, r4, #0x7c
    add     r0, r0, #0x1000
    add     r1, sp, #0x1c
    bl      func_02032388
    add     r0, r4, #0x7c
    mov     r1, #0
    add     r0, r0, #0x1000
    mov     r2, r1
    bl      WM_EndKeySharing_0x02032444
    add     r1, r4, #0x5000
    str     r0, [r1, #0xab4]
    mov     r0, #0x80000
    str     r0, [sp, #4]
    mov     r0, #0xbc000
    str     r0, [sp, #8]
    add     r0, r4, #0x7c
    ldr     r1, [r1, #0xab4]
    add     r0, r0, #0x1000
    add     r2, sp, #4
    bl      func_0203257c
    add     r1, r4, #0x5000
    add     r0, r4, #0x7c
    ldr     r1, [r1, #0xab4]
    add     r0, r0, #0x1000
    mov     r2, #0
    bl      func_0203281c
    ldr     r1, [pc, #0x90]
    add     r0, r4, #0x24
    bl      func_0202f7fc
    mov     r7, #0
    strh    r7, [sp, #0xc]
    add     r0, r4, #0x5000
    ldr     r0, [r0, #0xabc]
    mov     ip, #0
    cmp     r0, #0
    moveq   r7, #0xc
    mov     r6, #0x20
    mov     r5, #9
    mov     lr, #1
    add     r3, sp, #0xc
    add     r0, r4, #0x30
    add     r2, r4, #0x24
    mov     r1, #2
    strh    r7, [sp, #0xe]
    strh    r6, [sp, #0x10]
    strh    r5, [sp, #0x12]
    strh    lr, [sp, #0x14]
    strh    ip, [sp, #0x16]
    strh    ip, [sp, #0x18]
    strh    ip, [sp, #0x1a]
    bl      func_0202f834
    ldr     r0, [pc, #0x30]
    mov     r1, #0
    mov     r2, #6
    bl      GX_LoadBGPltt
    mov     r1, #0
    ldr     r0, [pc, #0x20]
    str     r1, [r4, #0x20]
    add     sp, sp, #0x2c
    ldmfd   sp!, {r4, r5, r6, r7, pc}
    dcd     data_ov007_0204d420
    dcd     data_ov007_0204d3d8
    dcd     data_ov007_0204d3e4
    dcd     0x00fffffc
    dcd     data_ov007_0204d3f8
    dcd     data_ov007_0204d3ac
    dcd     func_ov007_0204cf18
}
