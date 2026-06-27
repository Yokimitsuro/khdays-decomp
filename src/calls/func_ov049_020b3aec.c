extern void func_ov022_02091228(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0202a7dc(void);
extern void *data_ov049_020b4d00;

asm void func_ov049_020b3aec(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r1, =data_ov049_020b4d00
    mov     r5, r0
    add     r0, r5, #0x2000
    ldr     r1, [r1]
    ldr     r0, [r0, #0x644]
    add     r1, r1, #0xfc
    add     r4, r1, #0x2c00
    bl      func_ov022_02091228
    add     r0, r5, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    add     r0, r4, #4
    bl      func_0202a7dc
    ldmfd   sp!, {r3, r4, r5, pc}
}
