extern void func_ov081_020b9268(void *a, void *b, int c);
extern void func_ov081_020b92dc(void *a, void *b);

asm void func_ov081_020b8544(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldrsh   r2, [r1, #0xba]
    add     r4, r5, #0x2c
    add     r1, r4, #0x2c00
    bl      func_ov081_020b9268
    mov     r0, r5
    add     r1, r4, #0x2c00
    bl      func_ov081_020b92dc
    ldmfd   sp!, {r3, r4, r5, pc}
}
