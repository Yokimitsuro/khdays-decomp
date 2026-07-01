extern void func_ov107_020c9440(void);
extern void func_0203b898(void);
extern void func_0203bfb4(void);
extern void func_01fffc24(void);
extern void func_ov107_020c9074(void);
extern void func_01fffca8(void);
extern void func_ov107_020c32b8(void);
extern void func_0203355c(void);
extern void func_ov288_020d3a38(void);
extern void func_ov288_020d3a80(void);
extern void func_ov288_020d3b50(void);
extern void func_ov288_020d3ee8(void);
extern void func_ov288_020d3e68(void);
extern void func_ov288_020d3acc(void);
extern void func_ov288_020d3b34(void);
extern void func_ov288_020d3f44(void);
extern void func_ov288_020d3d98(void);
extern int data_02042270;
extern int data_02042264;
extern int data_02042258;

asm void func_ov288_020d3844(void)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x3c
    mov     r4, r0
    ldrh    r2, [r4]
    ldr     r1, =func_ov288_020d3a38
    mov     r3, #0x1000
    orr     r2, r2, #0x100
    strh    r2, [r4]
    str     r1, [r4, #8]
    ldr     r2, =func_ov288_020d3a80
    ldr     r1, =func_ov288_020d3b50
    str     r2, [r4, #0xc]
    str     r1, [r4, #0x1c]
    ldr     r2, =func_ov288_020d3ee8
    ldr     r1, =func_ov288_020d3e68
    str     r2, [r4, #0x30]
    str     r1, [r4, #0x38]
    ldr     r2, =func_ov288_020d3acc
    ldr     r1, =func_ov288_020d3b34
    str     r2, [r4, #0x20]
    str     r1, [r4, #0x24]
    ldr     r2, =func_ov288_020d3f44
    ldr     r1, =func_ov288_020d3d98
    str     r2, [r4, #0x1d0]
    str     r1, [r4, #0x1dc]
    mov     r1, #2
    strb    r1, [r4, #0x1c9]
    ldrh    lr, [r4, #0x60]
    add     r2, r4, #0x100
    mov     r1, #0
    mov     ip, lr, lsl #0x10
    mov     ip, ip, lsr #0x18
    orr     ip, ip, #0x44
    bic     lr, lr, #0xff00
    mov     ip, ip, lsl #0x18
    orr     ip, lr, ip, lsr #16
    strh    ip, [r4, #0x60]
    ldrh    ip, [r2, #0xae]
    orr     ip, ip, #0xc
    strh    ip, [r2, #0xae]
    ldrh    r2, [r4]
    orr     r2, r2, #0x8000
    strh    r2, [r4]
    str     r3, [r4, #0x70]
    str     r1, [r4, #0x64]
    str     r3, [r4, #0x68]
    str     r1, [r4, #0x6c]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x384]
    ldr     r0, [r4, #0x9c]
    ldr     r1, [r4, #0x384]
    bl      func_0203bfb4
    add     r0, r4, #0x398
    bl      func_01fffc24
    mov     r0, r4
    mov     r1, #1
    bl      func_ov107_020c9440
    bl      func_0203b898
    mov     r5, r0
    str     r0, [r4, #0x3c0]
    mov     r0, r4
    mov     r1, r5
    bl      func_ov107_020c9074
    ldr     r1, [r5, #0x5c]
    mov     r0, r4
    orr     r2, r1, #2
    mov     r1, #2
    str     r2, [r5, #0x5c]
    bl      func_ov107_020c9440
    bl      func_0203b898
    mov     r5, r0
    str     r0, [r4, #0x3c8]
    mov     r0, r4
    mov     r1, r5
    bl      func_ov107_020c9074
    ldr     r1, [r5, #0x5c]
    ldr     r0, =data_02042270
    orr     r1, r1, #2
    str     r1, [r5, #0x5c]
    add     r3, sp, #0xc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, =data_02042264
    add     r3, sp, #0x18
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, =data_02042258
    add     lr, sp, #0x24
    ldmia   r0, {r0, r1, r2}
    stmia   lr, {r0, r1, r2}
    mov     ip, #0x800
    mov     r3, #0
    str     ip, [sp, #0x38]
    str     ip, [sp, #0x34]
    str     ip, [sp, #0x30]
    str     ip, [sp, #4]
    str     r3, [sp]
    str     r3, [sp, #8]
    add     r0, r4, #0x22c
    mov     r1, #0x10
    mov     r2, #0x64
    bl      func_01fffca8
    str     r0, [r4, #0x388]
    add     r0, sp, #0
    bl      func_ov107_020c32b8
    ldr     r1, [r4, #0x388]
    str     r0, [r1]
    ldr     r0, =0x15b
    bl      func_0203355c
    add     sp, sp, #0x3c
    ldmfd   sp!, {r4, r5, pc}
}
