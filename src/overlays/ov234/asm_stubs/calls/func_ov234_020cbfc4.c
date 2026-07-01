extern void WM_EndKeySharing_0x020cc25c(void);
extern void WM_EndKeySharing_0x020cc268(void);
extern int data_ov234_020cd100;
extern void func_01fffca8(void);
extern void func_0203355c(void);
extern void func_0203b898(void);
extern void func_0203b9ac(void);
extern void func_0203bfb4(void);
extern void func_0203ca14(void);
extern void func_0203ca9c(void);
extern void func_ov107_020c319c(void);
extern void func_ov107_020c9074(void);
extern void func_ov107_020c9440(void);
extern void func_ov234_020cc1d8(void);
extern void func_ov234_020cc1fc(void);
extern void func_ov234_020cc274(void);
extern void func_ov234_020cc4e0(void);
extern void func_ov234_020cc518(void);
extern void func_ov234_020cc574(void);

asm void func_ov234_020cbfc4(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x2c
    ldr     r1, =func_ov234_020cc1d8
    mov     r4, r0
    str     r1, [r4, #8]
    ldr     r0, =func_ov234_020cc1fc
    ldr     r1, =func_ov234_020cc274
    str     r0, [r4, #0xc]
    str     r1, [r4, #0x1c]
    ldr     r0, =func_ov234_020cc518
    ldr     r1, =WM_EndKeySharing_0x020cc25c
    str     r0, [r4, #0x30]
    str     r1, [r4, #0x28]
    ldr     r0, =WM_EndKeySharing_0x020cc268
    ldr     r1, =func_ov234_020cc574
    str     r0, [r4, #0x2c]
    ldr     r0, =func_ov234_020cc4e0
    str     r1, [r4, #0x1d0]
    str     r0, [r4, #0x1dc]
    mov     r0, #2
    strb    r0, [r4, #0x1c9]
    add     r0, r4, #0x100
    ldrh    r1, [r0, #0xae]
    ldr     lr, =0xfffff7a8
    mov     r5, #0x17
    orr     r1, r1, #4
    strh    r1, [r0, #0xae]
    ldrh    r0, [r4, #0x60]
    ldr     r6, =0xfffff116
    add     r2, r5, #0x27
    mov     r3, r0, lsl #0x10
    mov     r3, r3, lsr #0x18
    add     r2, r2, #0x1c00
    str     r5, [sp, #8]
    orr     ip, r3, #0xa0
    bic     r8, r0, #0xff00
    mov     r0, ip, lsl #0x18
    orr     r0, r8, r0, lsr #16
    add     r1, r6, #0xd3
    strh    r0, [r4, #0x60]
    mov     r0, #0x700
    add     r3, r1, #0x1d00
    add     r7, lr, #0x164
    add     r1, r7, #0xc00
    ldr     r7, =data_ov234_020cd100
    add     ip, sp, #4
    ldr     r7, [r7]
    str     r6, [sp, #4]
    str     lr, [sp, #0xc]
    str     r0, [r4, #0x70]
    add     r5, r4, #0x1fc
    str     r3, [sp, #0x10]
    str     r2, [sp, #0x14]
    str     r1, [sp, #0x18]
    ldmia   ip!, {r0, r1, r2, r3}
    stmia   r5!, {r0, r1, r2, r3}
    ldmia   ip, {r0, r1}
    stmia   r5, {r0, r1}
    mov     r0, r4
    mov     r1, #0
    str     r7, [sp]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x384]
    ldr     r0, [r4, #0x9c]
    ldr     r1, [r4, #0x384]
    bl      func_0203bfb4
    ldr     r0, [r4, #0x384]
    add     r1, r4, #0x394
    bl      func_0203b9ac
    ldr     r0, [r4, #0x384]
    mov     r1, #0
    add     r0, r0, #4
    mov     r2, #0x380
    mov     r3, r1
    bl      func_0203ca14
    ldr     r1, =0x00000ccd
    add     r0, r4, #0xa0
    bl      func_0203ca9c
    mov     r1, r7
    mov     r0, r4
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x3bc]
    mov     r1, r0
    mov     r0, r4
    bl      func_ov107_020c9074
    ldr     r3, [r4, #0x3bc]
    mov     r1, #0
    ldr     r2, [r3, #0x5c]
    mov     r0, #0x1200
    orr     r2, r2, #2
    str     r2, [r3, #0x5c]
    str     r0, [sp, #0x28]
    str     r1, [sp, #0x1c]
    str     r1, [sp, #0x20]
    str     r1, [sp, #0x24]
    add     r0, r4, #0x22c
    mov     r1, #0x10
    mov     r2, #0x64
    bl      func_01fffca8
    str     r0, [r4, #0x388]
    add     r0, sp, #0x1c
    bl      func_ov107_020c319c
    ldr     r2, [r4, #0x388]
    mov     r1, #4
    str     r0, [r2]
    add     r0, r4, #0x144
    mov     r2, #0x64
    bl      func_01fffca8
    mov     r5, r0
    add     r0, r4, #0x64
    bl      func_ov107_020c319c
    str     r0, [r5]
    str     r0, [r4, #0x38c]
    mov     r0, #0
    str     r0, [r4, #0x3b8]
    mov     r0, #0x178
    bl      func_0203355c
    add     sp, sp, #0x2c
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, pc}
}
