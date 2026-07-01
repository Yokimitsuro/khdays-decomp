extern void func_02031384(void);
extern void func_0203b9fc(void);
extern void func_0203c7ac(void);

asm void func_ov288_020d3d98(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    sub     sp, sp, #0x10
    mov     r6, r0
    ldr     r0, [r6, #0x50]
    mov     r5, r1
    cmp     r0, #1
    mov     r4, r2
    addne   sp, sp, #0x10
    ldmnefd sp!, {r4, r5, r6, pc}
    add     r1, sp, #0
    mov     r0, #0
    strh    r0, [r1]
    strh    r0, [r1, #2]
    strh    r0, [r1, #4]
    strh    r0, [r1, #6]
    strh    r0, [r1, #8]
    strh    r0, [r1, #0xa]
    strh    r0, [r1, #0xc]
    ldrh    r3, [r6, #2]
    mov     r0, #4
    mov     r2, #5
    strh    r3, [r1]
    strb    r0, [r1, #3]
    strb    r2, [r1, #2]
    ldr     r2, [r6, #0x38c]
    mov     r3, r4, lsl #0x1f
    add     r2, r5, r2, lsl #2
    and     r2, r2, #0xff
    and     r2, r2, #0x7f
    orr     r2, r2, r3, lsr #24
    strb    r2, [sp, #4]
    mov     r2, #0xe
    bl      func_02031384
    mov     r1, r5, lsl #0x10
    mov     r2, r1, asr #0x10
    ldr     r0, [r6, #0x384]
    mov     r3, r4
    mov     r1, #0
    bl      func_0203b9fc
    ldr     r1, [r6, #0x38c]
    ldr     r0, [r6, #0x384]
    add     r1, r5, r1, lsl #2
    mov     r1, r1, lsl #0x10
    mov     r2, r1, asr #0x10
    mov     r3, r4
    mov     r1, #2
    bl      func_0203b9fc
    ldr     r0, [r6, #0x384]
    mov     r1, #0
    bl      func_0203c7ac
    add     sp, sp, #0x10
    ldmfd   sp!, {r4, r5, r6, pc}
}
