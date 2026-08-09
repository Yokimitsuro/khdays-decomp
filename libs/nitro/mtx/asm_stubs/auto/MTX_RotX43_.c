typedef signed long fx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

/* Canonical NitroSDK THUMB primitive for a 4x3 X-axis rotation matrix. */
asm void MTX_RotX43_(MtxFx43 *dst, fx32 sinVal, fx32 cosVal)
{
    str     r1, [r0, #0x14]
    neg     r1, r1
    str     r1, [r0, #0x1c]
    mov     r1, #1
    lsl     r1, r1, #12
    stmia   r0!, {r1}
    mov     r3, #0
    mov     r1, #0
    stmia   r0!, {r1, r3}
    stmia   r0!, {r1, r2}
    str     r1, [r0, #4]
    add     r0, #12
    stmia   r0!, {r2, r3}
    stmia   r0!, {r1, r3}
    bx      lr
}
