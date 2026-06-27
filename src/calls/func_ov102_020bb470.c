extern void VEC_Add(void);
extern char data_ov102_020bb920[];
extern void func_01fff774(void);
extern void func_0202af1c(void);
extern void func_02030788(void);
extern void func_ov022_02083f90(void);
extern void func_ov022_02095524(void);
extern void func_ov022_0209fe20(void);
extern void func_ov022_020a35f4(void);
extern void func_ov102_020bb1f4(void);

asm void func_ov102_020bb470(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x18
    ldr     r1, [pc, #0x310]
    mov     r8, r0
    ldr     r0, [r1]
    mov     r4, #0
    add     r0, r0, #0xc50
    add     r5, r0, #0x2000
    bl      func_02030788
    cmp     r0, #0
    bne     _L0048
    add     r0, r8, #0x64
    ldr     r2, [r8, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r8, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L0048:
    bl      func_02030788
    cmp     r0, #0
    bne     _L0070
    add     r0, r8, #0x6c
    ldr     r2, [r8, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r8, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L0070:
    add     r1, sp, #0xc
    mov     r0, r8
    bl      func_ov022_0209fe20
    ldr     r0, [sp, #0x10]
    cmp     r0, #0
    strne   r0, [r8, #0x58]
    bne     _L00b8
    ldr     r0, [r8, #0x24]
    tst     r0, #4
    bne     _L00b8
    ldr     r1, [r8]
    ldr     r0, [r8, #4]
    orr     r1, r1, #0
    str     r1, [r8]
    orr     r0, r0, #0x4000
    str     r0, [r8, #4]
    mov     r0, #0
    str     r0, [r8, #0x58]
_L00b8:
    add     r0, sp, #0xc
    add     r3, sp, #0
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, #0
    add     r2, r8, #0x98
    str     r0, [sp, #4]
    add     r0, r2, #0x400
    mov     r1, r3
    add     r2, r2, #0x400
    bl      VEC_Add
    ldr     r0, [r5, #8]
    cmp     r0, #0
    bne     _L01a8
    ldr     r0, [r5]
    mov     r6, #0xf000
    cmp     r0, #0
    ldrh    r0, [r8, #0x1c]
    mov     r7, #4
    movne   r6, #0x12000
    add     r0, r0, #0xfb
    add     r0, r0, #0xff00
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    movne   r7, #0x3e8
    cmp     r0, #1
    bhi     _L015c
    add     r0, r8, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    beq     _L015c
    ldr     r0, [r5, #0x124]
    cmp     r0, #0
    ble     _L015c
    cmp     r0, r7
    bge     _L015c
    ldr     r0, [r5, #0x120]
    cmp     r0, #0x3000
    movge   r0, #1
    strge   r0, [r5, #4]
_L015c:
    ldr     r0, [r5, #4]
    cmp     r0, #0
    beq     _L018c
    ldr     r0, [r8, #0x7b0]
    cmp     r0, r6
    blt     _L01a8
    mov     r0, r8
    bl      func_ov102_020bb1f4
    mov     r0, #0
    str     r0, [r5, #4]
    str     r0, [r5, #0x120]
    b       _L01a8
_L018c:
    bl      func_ov022_02083f90
    ldr     r1, [r5, #0x120]
    add     r0, r1, r0
    str     r0, [r5, #0x120]
    cmp     r0, #0x9000
    movge   r0, #1
    strge   r0, [r5, #8]
_L01a8:
    ldr     r0, [r5, #8]
    cmp     r0, #0
    bne     _L0208
    ldr     r0, [r5]
    mov     r1, #0x12000
    cmp     r0, #0
    mov     r5, #0xc000
    ldr     r0, [r8, #0x7b0]
    movne   r1, #0x15000
    movne   r5, #0xf000
    cmp     r0, r1
    blt     _L0208
    ldr     r0, [r8, #0x20]
    mov     r2, r5
    add     r0, r0, #4
    mov     r1, #0
    bl      func_01fff774
    str     r5, [r8, #0x7b0]
    ldr     r1, [r8]
    ldr     r0, [r8, #4]
    orr     r1, r1, #0x20000000
    str     r1, [r8]
    orr     r0, r0, #0
    str     r0, [r8, #4]
_L0208:
    ldr     r1, [r8, #0x668]
    mov     r0, r8
    blx     r1
    ldrb    r1, [r8, #0x694]
    and     r0, r0, #0xff
    mov     r0, r0, lsl #0x1f
    bic     r1, r1, #2
    orr     r1, r1, r0, lsr #30
    and     r0, r1, #0xff
    mov     r0, r0, lsl #0x1e
    strb    r1, [r8, #0x694]
    movs    r0, r0, lsr #0x1f
    beq     _L0294
    ldr     r1, [r8]
    ldr     r0, [r8, #4]
    orr     r1, r1, #0
    str     r1, [r8]
    orr     r0, r0, #0x20000
    str     r0, [r8, #4]
    ldr     r1, [r8, #0x20]
    ldr     r0, [r1]
    tst     r0, #0x20
    bne     _L026c
    add     r0, r1, #4
    bl      func_0202af1c
_L026c:
    bl      func_02030788
    cmp     r0, #0
    bne     _L0294
    add     r0, r8, #0x64
    ldr     r2, [r8, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #2
    str     r2, [r8, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L0294:
    ldrb    r0, [r8, #0x694]
    mov     r0, r0, lsl #0x1e
    movs    r0, r0, lsr #0x1f
    beq     _L0314
    ldr     r1, [r8]
    ldr     r0, [r8, #4]
    orr     r1, r1, #4
    str     r1, [r8]
    orr     r0, r0, #0
    mov     r1, #0
    str     r0, [r8, #4]
    str     r1, [r8, #0x4a0]
    str     r1, [r8, #0x49c]
    str     r1, [r8, #0x498]
    str     r1, [r8, #0x6a0]
    str     r1, [r8, #0x69c]
    str     r1, [r8, #0x698]
    ldr     r0, [r8, #0x24]
    tst     r0, #4
    beq     _L0304
    ldr     r2, [r8, #0x664]
    mov     r0, r8
    blx     r2
    mov     r0, r8
    mov     r1, #0
    bl      func_ov022_020a35f4
    mov     r4, r0
    b       _L0314
_L0304:
    mov     r0, r8
    mov     r1, #2
    bl      func_ov022_020a35f4
    mov     r4, r0
_L0314:
    mov     r0, r4
    add     sp, sp, #0x18
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
    dcd     data_ov102_020bb920
}
