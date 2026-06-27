extern void func_ov107_020c9440(void);
extern void func_0203b898(void);
extern void func_0203bfb4(void);
extern void func_0203ca14(void);
extern void func_0203b9fc(void);
extern void func_ov107_020c92b0(void);
extern void func_01fffca8(void);
extern void func_ov107_020c319c(void);
extern void func_0203355c(void);
extern void func_ov295_020d39a0(void);
extern void func_ov295_020d39bc(void);
extern void func_ov295_020d3a20(void);
extern void func_ov295_020d3a6c(void);
extern char data_02041dc8[];

asm void func_ov295_020d3844(void *r0)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x14
    ldr     r2, [pc, #0x134]
    mov     r4, r0
    str     r2, [r4, #8]
    ldr     r1, [pc, #0x12c]
    ldr     r2, [pc, #0x12c]
    str     r1, [r4, #0xc]
    str     r2, [r4, #0x30]
    ldr     r1, [pc, #0x124]
    add     r2, r4, #0x100
    str     r1, [r4, #0x1d0]
    mov     r1, #2
    strb    r1, [r4, #0x1c9]
    mov     r1, #0x1200
    str     r1, [r4, #0x70]
    mov     r1, #0
    str     r1, [r4, #0x64]
    str     r1, [r4, #0x68]
    str     r1, [r4, #0x6c]
    ldrh    r3, [r2, #0xae]
    orr     r3, r3, #0x10
    strh    r3, [r2, #0xae]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r4, #0x384]
    ldr     r0, [r4, #0x9c]
    ldr     r1, [r4, #0x384]
    bl      func_0203bfb4
    mov     r1, #0
    ldr     r0, [r4, #0x384]
    sub     r2, r1, #0x1200
    add     r0, r0, #4
    mov     r3, r1
    bl      func_0203ca14
    mov     r1, #0
    ldr     r0, [r4, #0x384]
    mov     r2, r1
    mov     r3, #1
    bl      func_0203b9fc
    ldr     r0, [r4, #0x384]
    mov     r1, #4
    mov     r2, #0
    mov     r3, #1
    bl      func_0203b9fc
    mov     r0, #0x2000
    mov     r1, #2
    str     r0, [sp]
    mov     r0, r4
    mov     r2, r1
    mov     r3, #0
    bl      func_ov107_020c92b0
    ldr     r0, [pc, #0x7c]
    add     r5, sp, #4
    ldmia   r0, {r0, r1, r2}
    stmia   r5, {r0, r1, r2}
    mov     r3, #0x1200
    str     r3, [sp, #0x10]
    add     r0, r4, #0x22c
    mov     r1, #0x10
    mov     r2, #0x64
    bl      func_01fffca8
    str     r0, [r4, #0x388]
    mov     r0, r5
    bl      func_ov107_020c319c
    ldr     r2, [r4, #0x388]
    mov     r1, #4
    str     r0, [r2]
    add     r0, r4, #0x144
    mov     r2, #0x64
    bl      func_01fffca8
    mov     r5, r0
    add     r0, sp, #4
    bl      func_ov107_020c319c
    mov     r1, r0
    str     r0, [r5]
    ldr     r0, [pc, #0x20]
    str     r1, [r4, #0x390]
    bl      func_0203355c
    add     sp, sp, #0x14
    ldmfd   sp!, {r4, r5, pc}
    dcd     func_ov295_020d39a0
    dcd     func_ov295_020d39bc
    dcd     func_ov295_020d3a20
    dcd     func_ov295_020d3a6c
    dcd     data_02041dc8
    dcd     0x00000171
}
