extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_ov107_020c0b90(int a, int b, int c, int d);
extern int func_01fffe14(void);

asm void func_ov234_020ccf80(void *r0)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x14
    ldr     r4, [r0, #4]
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    addeq   sp, sp, #0x14
    ldmeqfd sp!, {r4, r5, pc}
    ldr     r0, [r4]
    ldrb    r1, [r0, #0x17a]
    mov     r1, r1, lsl #0x1f
    movs    r1, r1, lsr #0x1f
    addeq   sp, sp, #0x14
    ldmeqfd sp!, {r4, r5, pc}
    ldr     r3, [r4, #8]
    mov     r1, #0x178
    mov     r2, #4
    bl      func_ov107_020c5af8
    ldr     r5, [r4]
    add     lr, sp, #8
    add     r0, r5, #0x74
    ldmia   r0, {r0, r1, r2}
    stmia   lr, {r0, r1, r2}
    ldr     r0, [sp, #0xc]
    mov     r12, #0
    sub     r0, r0, #0x400
    str     r0, [sp, #0xc]
    str     r12, [sp, #4]
    sub     r3, sp, #8
    ldmia   lr, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r5
    mov     r1, r12
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
    ldrsh   r0, [r4, #0x70]
    cmp     r0, #4
    blt     _Le4
    mov     r0, #0
    str     r0, [r4, #0x64]
    mov     r0, #0xff0
    str     r0, [r4, #0x48]
    ldr     r5, [r4]
    bl      func_01fffe14
    and     r0, r0, #0xff
    str     r0, [sp, #4]
    add     r0, r5, #0x74
    sub     r3, sp, #8
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r5
    mov     r1, #3
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
    ldr     r0, [r4]
    mov     r1, #3
    strb    r1, [r0, #0x1c7]
    b       _L144
_Le4:
    cmp     r0, #3
    bne     _L11c
    ldr     r5, [r4]
    bl      func_01fffe14
    and     r0, r0, #0xff
    str     r0, [sp, #4]
    add     r0, r5, #0x74
    sub     r3, sp, #8
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r5
    mov     r1, #6
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
_L11c:
    ldrsh   r2, [r4, #0x70]
    mov     r1, #0
    mov     r0, #0xff0
    add     r2, r2, #1
    strh    r2, [r4, #0x70]
    str     r1, [r4, #0x64]
    str     r0, [r4, #0x48]
    ldr     r0, [r4]
    mov     r1, #2
    strb    r1, [r0, #0x1c7]
_L144:
    mov     r0, #0
    str     r0, [r4, #0x44]
    add     sp, sp, #0x14
    ldmfd   sp!, {r4, r5, pc}
}
