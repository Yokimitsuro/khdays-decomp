extern void func_ov022_02091228(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_ov002_02051fc8(void);
extern void func_0202a7dc(void);

asm void func_ov045_020b4178(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    add     r0, r4, #0x138
    add     r0, r0, #0x2c00
    add     r1, r4, #0x910
    bl      func_ov002_02051fc8
    add     r0, r4, #0x18c
    add     r0, r0, #0x2c00
    add     r1, r4, #0x910
    bl      func_ov002_02051fc8
    add     r0, r4, #0x1f4
    add     r0, r0, #0x2c00
    bl      func_0202a7dc
    ldmfd   sp!, {r4, pc}
}
