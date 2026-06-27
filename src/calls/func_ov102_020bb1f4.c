extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern char data_0203d210[];
extern char data_ov102_020bb7ec[];
extern char data_ov102_020bb81c[];
extern char data_ov102_020bb920[];
extern void func_02020400(void);
extern void func_020307f4(void);
extern void func_ov022_02091324(void);

asm void func_ov102_020bb1f4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0xf8
    ldr     r6, [pc, #0x1c0]
    add     r5, sp, #0
    mov     r10, r0
    ldmia   r6!, {r0, r1, r2, r3}
    stmia   r5!, {r0, r1, r2, r3}
    ldmia   r6!, {r0, r1, r2, r3}
    stmia   r5!, {r0, r1, r2, r3}
    ldmia   r6, {r0, r1, r2, r3}
    ldr     r4, [pc, #0x1a4]
    stmia   r5, {r0, r1, r2, r3}
    ldr     r0, [r4]
    ldr     r7, [pc, #0x19c]
    add     r0, r0, #0xc50
    add     r6, sp, #0x98
    add     r5, r0, #0x2000
    mov     r4, #6
_L0048:
    ldmia   r7!, {r0, r1, r2, r3}
    stmia   r6!, {r0, r1, r2, r3}
    subs    r4, r4, #1
    bne     _L0048
    ldr     r0, [r10, #0x20]
    ldr     r2, [pc, #0x178]
    ldrh    r1, [r0, #0x80]
    add     r0, sp, #0x30
    sub     r1, r1, #0x8000
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    mov     r1, r1, asr #4
    mov     r3, r1, lsl #1
    add     r1, r3, #1
    mov     r3, r3, lsl #1
    mov     r1, r1, lsl #1
    ldrsh   r3, [r2, r3]
    ldrsh   r2, [r2, r1]
    rsb     r1, r3, #0
    rsb     r2, r2, #0
    bl      MTX_RotY33_
    add     r0, r10, #0x8c
    add     r0, r0, #0x400
    add     r3, sp, #0x54
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r5]
    cmp     r0, #0
    addne   r9, sp, #0x98
    movne   r8, #8
    movne   r7, #2
    bne     _L00d4
    mov     r8, #4
    add     r9, sp, #0
    mov     r7, #1
_L00d4:
    cmp     r7, #0
    mov     r6, #0
    addle   sp, sp, #0xf8
    ldmlefd sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    add     r11, sp, #0x6c
    add     r4, sp, #0x60
_L00ec:
    mov     r0, #0
    strh    r0, [sp, #0x7c]
    mov     r0, r0
    strh    r0, [sp, #0x7a]
    strh    r0, [sp, #0x78]
    ldr     r0, [r5, #0x124]
    mov     r1, r8
    bl      func_02020400
    mov     r0, #0xc
    mla     r0, r1, r0, r9
    add     r1, sp, #0x30
    mov     r2, r4
    bl      MTX_MultVec33
    add     r0, sp, #0x54
    mov     r1, r4
    mov     r2, r11
    bl      VEC_Add
    mov     r0, #0
    str     r0, [sp, #0x80]
    mov     r0, #1
    str     r0, [sp, #0x88]
    mov     r0, #0
    str     r0, [sp, #0x8c]
    mov     r0, #7
    str     r0, [sp, #0x84]
    mov     r0, #3
    bl      func_020307f4
    str     r0, [sp, #0x90]
    mov     r0, #0
    str     r0, [sp, #0x94]
    mov     r0, #0x1400
    strh    r0, [sp, #0x7e]
    ldr     r0, [r5]
    cmp     r0, #0
    beq     _L0188
    mov     r0, #1
    str     r0, [sp, #0x94]
    mov     r0, #0xd00
    strh    r0, [sp, #0x7e]
_L0188:
    mov     r0, r10
    mov     r1, r11
    bl      func_ov022_02091324
    ldr     r1, [r10]
    tst     r1, #0x10000
    bne     _L01b0
    mov     r0, #3
    strb    r0, [r10, #0x47a]
    mov     r0, #0
    strb    r0, [r10, #0x47b]
_L01b0:
    ldr     r0, [r5, #0x124]
    add     r6, r6, #1
    add     r0, r0, #1
    str     r0, [r5, #0x124]
    cmp     r6, r7
    blt     _L00ec
    add     sp, sp, #0xf8
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    dcd     data_ov102_020bb7ec
    dcd     data_ov102_020bb920
    dcd     data_ov102_020bb81c
    dcd     data_0203d210
}
