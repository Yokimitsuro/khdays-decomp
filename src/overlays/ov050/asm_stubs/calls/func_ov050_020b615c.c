extern void func_ov022_02091228(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0202a7dc(void);
extern void *data_ov050_020b75c0;

asm void func_ov050_020b615c(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r1, =data_ov050_020b75c0
    mov     r4, r0
    add     r0, r4, #0x2000
    ldr     r1, [r1]
    ldr     r0, [r0, #0x644]
    add     r1, r1, #0x2c
    add     r5, r1, #0x2c00
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x60
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    add     r5, r5, #0x14
    mov     r4, #0
_loop:
    mov     r0, r5
    bl      func_0202a7dc
    add     r4, r4, #1
    cmp     r4, #2
    add     r5, r5, #0x118
    blt     _loop
    ldmfd   sp!, {r3, r4, r5, pc}
}
