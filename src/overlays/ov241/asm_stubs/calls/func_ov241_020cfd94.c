extern void func_ov107_020c9440(void);
extern void func_0203b898(void);
extern void func_0203bfb4(void);
extern void func_0203bdfc(void);
extern void func_02014e18(void);
extern void func_0203ca14(void);
extern void func_ov107_020c9e50(void);
extern void func_ov107_020c9074(void);
extern void func_0203b9fc(void);
extern void func_0203bf44(void);
extern void func_01fffca8(void);
extern void func_ov107_020c319c(void);
extern void func_0203355c(void);
extern void func_ov241_020d0024(void);
extern void func_ov241_020d008c(void);
extern void func_ov241_020d0170(void);
extern void func_ov241_020d0104(void);
extern void func_ov241_020d00d4(void);
extern void data_ov241_020d0c84(void);
extern void func_ov241_020cfc04(void);
extern void data_ov241_020d0cc4(void);

asm void func_ov241_020cfd94(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0x10
    ldr     r1, =func_ov241_020d0024
    mov     r6, r0
    str     r1, [r6, #8]
    ldr     r2, =func_ov241_020d008c
    ldr     r1, =func_ov241_020d0170
    str     r2, [r6, #0xc]
    str     r1, [r6, #0x30]
    ldr     r2, =func_ov241_020d0104
    ldr     r1, =func_ov241_020d00d4
    str     r2, [r6, #0x38]
    str     r1, [r6, #0x1dc]
    mov     r1, #2
    strb    r1, [r6, #0x1c9]
    ldr     r2, =0x000004cd
    mov     r1, #0
    str     r2, [r6, #0x70]
    str     r1, [r6, #0x64]
    str     r2, [r6, #0x68]
    str     r1, [r6, #0x6c]
    add     r2, r6, #0x100
    ldrh    r3, [r2, #0xae]
    orr     r3, r3, #8
    strh    r3, [r2, #0xae]
    ldrh    r3, [r6, #0x60]
    mov     r2, r3, lsl #0x10
    mov     r2, r2, lsr #0x18
    orr     r2, r2, #0x20
    bic     r3, r3, #0xff00
    mov     r2, r2, lsl #0x18
    orr     r2, r3, r2, lsr #0x10
    strh    r2, [r6, #0x60]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r6, #0x384]
    ldr     r0, [r6, #0x9c]
    ldr     r1, [r6, #0x384]
    bl      func_0203bfb4
    ldr     r0, =data_ov241_020d0c84
    add     r4, sp, #4
    ldmia   r0, {r0, r1, r2}
    stmia   r4, {r0, r1, r2}
    mov     r5, #0
_loopA:
    ldr     r1, [r4, r5, lsl #2]
    cmp     r1, #0
    beq     _skipA
    ldr     r0, [r6, #0x384]
    bl      func_0203bdfc
    add     r1, r6, r5, lsl #1
    add     r1, r1, #0x300
    strh    r0, [r1, #0xac]
_skipA:
    add     r5, r5, #1
    cmp     r5, #3
    blt     _loopA
    ldr     r1, [r6, #0x384]
    mov     r0, #3
    ldr     r2, [r1, #0x88]
    ldr     r1, =func_ov241_020cfc04
    str     r6, [r2, #0x4c]
    str     r0, [sp]
    ldr     r0, [r6, #0x384]
    mov     r2, #0
    ldr     r0, [r0, #0x88]
    mov     r3, #6
    add     r0, r0, #0x20
    bl      func_02014e18
    ldr     r0, [r6, #0x384]
    mov     r1, #0
    mov     r3, r1
    add     r0, r0, #4
    mov     r2, #0x200
    bl      func_0203ca14
    mov     r0, r6
    mov     r1, #1
    bl      func_ov107_020c9440
    ldr     r1, =data_ov241_020d0cc4
    bl      func_ov107_020c9e50
    mov     r5, #0
    mov     r4, #2
    mov     r10, #1
    str     r0, [r6, #0x39c]
    mov     r11, r5
    mov     r9, r4
    mov     r8, r5
    mov     r7, r10
_loopB:
    mov     r0, r6
    mov     r1, r4
    bl      func_ov107_020c9440
    bl      func_0203b898
    add     r1, r6, r5, lsl #2
    str     r0, [r1, #0x38c]
    mov     r1, r0
    mov     r0, r6
    bl      func_ov107_020c9074
    add     ip, r6, r5, lsl #2
    ldr     r0, [ip, #0x38c]
    mov     r1, r11
    ldr     r3, [r0, #0x5c]
    mov     r2, r11
    bic     r3, r3, #1
    orr     r3, r3, #1
    str     r3, [r0, #0x5c]
    ldr     r0, [ip, #0x38c]
    mov     r3, r10
    ldr     lr, [r0, #0x5c]
    orr     lr, lr, #2
    str     lr, [r0, #0x5c]
    ldr     r0, [ip, #0x38c]
    bl      func_0203b9fc
    add     r0, r6, r5, lsl #2
    ldr     r0, [r0, #0x38c]
    mov     r1, r9
    mov     r2, r8
    mov     r3, r7
    bl      func_0203b9fc
    add     r1, r6, r5, lsl #2
    ldr     r0, [r6, #0x9c]
    ldr     r1, [r1, #0x38c]
    bl      func_0203bfb4
    add     r5, r5, #1
    cmp     r5, #3
    blt     _loopB
    bl      func_0203bf44
    str     r0, [r6, #0x3a0]
    ldr     r0, [r6, #0x9c]
    ldr     r1, [r6, #0x3a0]
    bl      func_0203bfb4
    ldr     r3, [r6, #0x3a0]
    mov     r0, r6
    ldr     r2, [r3, #0x5c]
    mov     r1, #3
    bic     r2, r2, #1
    orr     r2, r2, #1
    str     r2, [r3, #0x5c]
    bl      func_ov107_020c9440
    bl      func_0203b898
    str     r0, [r6, #0x388]
    ldr     r0, [r6, #0x3a0]
    ldr     r1, [r6, #0x388]
    bl      func_0203bfb4
    add     r0, r6, #0x144
    mov     r1, #4
    mov     r2, #0x64
    bl      func_01fffca8
    mov     r4, r0
    add     r0, r6, #0x64
    bl      func_ov107_020c319c
    str     r0, [r4]
    str     r0, [r6, #0x398]
    ldr     r0, =0x0000013a
    bl      func_0203355c
    add     sp, sp, #0x10
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
