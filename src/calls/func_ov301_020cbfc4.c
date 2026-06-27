extern void func_ov107_020c9440(void *r0, int r1);
extern void *func_0203b898(void);
extern void func_0203bfb4(void *r0, void *r1);
extern void *func_01fffca8(void *r0, int r1, int r2);
extern void *func_ov107_020c3210(void *r0);
extern void *func_ov107_020c319c(void *r0);
extern void func_ov301_020cc15c(void);
extern void func_ov301_020cc178(void);
extern void func_ov301_020cc240(void);
extern void WM_EndKeySharing_0x020cc1d8(void);
extern void WM_EndKeySharing_0x020cc1e4(void);
extern void func_ov301_020cc28c(void);
extern void func_ov301_020cc1f0(void);
extern int data_02041dc8;
extern int data_02042264;

asm void func_ov301_020cbfc4(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x38
    ldr     r1, =func_ov301_020cc15c
    mov     r4, r0
    str     r1, [r4, #8]
    ldr     r3, =0xfffff7a8
    ldr     r0, =func_ov301_020cc178
    ldr     r6, =0xfffff116
    str     r0, [r4, #0xc]
    ldr     r1, =func_ov301_020cc240
    ldr     r0, =WM_EndKeySharing_0x020cc1d8
    str     r1, [r4, #0x30]
    str     r0, [r4, #0x28]
    mov     r5, #0x17
    ldr     r7, =WM_EndKeySharing_0x020cc1e4
    add     r0, r6, #0xd3
    add     r2, r0, #0x1d00
    add     ip, r3, #0x164
    add     r0, ip, #0xc00
    add     r1, r5, #0x27
    add     r1, r1, #0x1c00
    str     r5, [sp, #4]
    ldr     lr, =func_ov301_020cc28c
    str     r7, [r4, #0x2c]
    str     lr, [r4, #0x1d0]
    ldr     ip, =func_ov301_020cc1f0
    mov     lr, #0
    str     ip, [r4, #0x1dc]
    mov     ip, #2
    strb    ip, [r4, #0x1c9]
    mov     ip, #0x1900
    str     ip, [r4, #0x70]
    str     lr, [r4, #0x64]
    mov     ip, #0x400
    str     ip, [r4, #0x68]
    add     ip, sp, #0
    str     r6, [sp]
    str     lr, [r4, #0x6c]
    add     r5, r4, #0x1fc
    str     r3, [sp, #8]
    str     r2, [sp, #0xc]
    str     r1, [sp, #0x10]
    str     r0, [sp, #0x14]
    ldmia   ip!, {r0, r1, r2, r3}
    stmia   r5!, {r0, r1, r2, r3}
    ldmia   ip, {r0, r1}
    stmia   r5, {r0, r1}
    mov     r0, r4
    mov     r1, lr
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x384]
    ldr     r0, [r4, #0x9c]
    ldr     r1, [r4, #0x384]
    bl      func_0203bfb4
    add     r0, r4, #0x100
    ldrh    r2, [r0, #0xae]
    ldr     r1, =data_02041dc8
    add     lr, sp, #0x18
    orr     r2, r2, #0x10
    strh    r2, [r0, #0xae]
    ldmia   r1, {r0, r1, r2}
    stmia   lr, {r0, r1, r2}
    ldr     ip, =data_02042264
    add     r6, sp, #0x24
    ldmia   ip, {r0, r1, r2}
    stmia   r6, {r0, r1, r2}
    mov     r5, #0x4000
    mov     r3, #0x1900
    str     r5, [sp, #0x30]
    str     r3, [sp, #0x34]
    add     r0, r4, #0x22c
    mov     r1, #0x10
    mov     r2, #0x64
    bl      func_01fffca8
    str     r0, [r4, #0x388]
    add     r0, sp, #0x18
    bl      func_ov107_020c3210
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
    add     sp, sp, #0x38
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
