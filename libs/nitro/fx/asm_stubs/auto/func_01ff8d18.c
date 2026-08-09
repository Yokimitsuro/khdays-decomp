typedef signed long fx32;

typedef struct Vecx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

/* NitroSDK VEC_Normalize. The ARM body preserves the shipped instruction schedule. */
asm fx32 func_01ff8d18(const VecFx32 *src, VecFx32 *dst)
{
    stmdb   sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    ldr     r2, [r0, #4]
    ldr     r3, [r0]
    smull   r6, r5, r2, r2
    smlal   r6, r5, r3, r3
    ldr     r2, [r0, #8]
    ldr     r4, =0x04000280
    smlal   r6, r5, r2, r2
    mov     r3, #2
    strh    r3, [r4]
    mov     r3, #0
    str     r3, [r4, #0x10]
    mov     r3, #0x1000000
    str     r3, [r4, #0x14]
    str     r6, [r4, #0x18]
    mov     r2, r5, lsl #2
    str     r5, [r4, #0x1c]
    mov     r3, #1
    strh    r3, [r4, #0x30]
    mov     r3, r6, lsl #2
    str     r3, [r4, #0x38]
    orr     r2, r2, r6, lsr #30
    str     r2, [r4, #0x3c]
waitSqrt:
    ldrh    r2, [r4, #0x30]
    tst     r2, #0x8000
    bne     waitSqrt
    ldr     r2, =0x040002b4
    ldr     ip, [r2]
    sub     r3, r2, #0x34
waitDiv:
    ldrh    r2, [r3]
    tst     r2, #0x8000
    bne     waitDiv
    ldr     r9, =0x040002a0
    ldr     r5, [r0]
    ldr     r8, [r9]
    mov     r7, ip, asr #0x1f
    umull   r3, r2, r8, ip
    umull   lr, r6, r3, r5
    mov     r4, r5, asr #0x1f
    mla     r2, r8, r7, r2
    ldr     r7, [r9, #4]
    mla     r6, r3, r4, r6
    mla     r2, r7, ip, r2
    mla     r6, r2, r5, r6
    adds    r4, lr, #0
    adc     r4, r6, #0x1000
    mov     r4, r4, asr #0xd
    str     r4, [r1]
    ldr     lr, [r0, #4]
    add     ip, ip, #1
    umull   r6, r5, r3, lr
    mov     r4, lr, asr #0x1f
    mla     r5, r3, r4, r5
    mla     r5, r2, lr, r5
    adds    r4, r6, #0
    adc     r4, r5, #0x1000
    mov     r4, r4, asr #0xd
    str     r4, [r1, #4]
    ldr     lr, [r0, #8]
    mov     r0, ip, asr #1
    umull   ip, r4, r3, lr
    adds    ip, ip, #0
    mov     ip, lr, asr #0x1f
    mla     r4, r3, ip, r4
    mla     r4, r2, lr, r4
    adc     r2, r4, #0x1000
    mov     r2, r2, asr #0xd
    str     r2, [r1, #8]
    ldmia   sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
