extern void FX_Atan2(void);
extern int data_ov042_020b4800;
extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov042_020b44e8(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    ldr     r2, =data_ov042_020b4800
    mov     r8, r0
    ldr     r2, [r2]
    mov     r5, #0
    add     r0, r2, #0x2c
    add     r4, r0, #0x2c00
    mov     r7, r1
    mov     r2, r5
    mov     r1, r4
_L_0028:
    ldr     r0, [r1, #0x14]
    cmp     r0, #0
    bne     _L_0044
    add     r1, r4, #0x14
    mov     r0, #0x10c
    mla     r5, r2, r0, r1
    b       _L_0054
_L_0044:
    add     r2, r2, #1
    cmp     r2, #7
    add     r1, r1, #0x10c
    blt     _L_0028
_L_0054:
    cmp     r5, #0
    ldmeqfd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r3, [r4, #0xc]
    ldr     r1, =0x55555556
    mov     r2, #3
    smull   r0, r6, r1, r3
    add     r6, r6, r3, lsr #31
    smull   r0, r1, r2, r6
    sub     r6, r3, r0
    mov     r1, r6, lsl #0x10
    mov     ip, #1
    add     r0, r5, #4
    add     r2, r5, #0xe4
    mov     r3, r1, asr #0x10
    mov     r1, #0
    str     ip, [r5]
    bl      func_0202accc
    mov     r1, r6, lsl #0x10
    add     r0, r5, #4
    add     r2, r5, #0xe4
    mov     r3, r1, asr #0x10
    mov     r1, #2
    bl      func_0202accc
    mov     r0, r6, lsl #0x10
    mov     r3, r0, asr #0x10
    add     r0, r5, #4
    mov     r1, #1
    add     r2, r5, #0xe4
    bl      func_0202accc
    add     r0, r5, #4
    mov     r1, #0
    mov     r2, r1
    bl      func_01fff774
    add     r0, r5, #4
    mov     r1, #2
    mov     r2, #0
    bl      func_01fff774
    add     r0, r5, #4
    mov     r1, #1
    mov     r2, #0
    bl      func_01fff774
    add     r3, r5, #0xa8
    ldmia   r8, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r7]
    ldr     r1, [r7, #8]
    rsb     r0, r0, #0
    rsb     r1, r1, #0
    bl      FX_Atan2
    strh    r0, [r5, #0x80]
    ldrh    r0, [r5, #4]
    orr     r0, r0, #0x20
    strh    r0, [r5, #4]
    ldr     r0, [r4, #0xc]
    add     r0, r0, #1
    str     r0, [r4, #0xc]
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
