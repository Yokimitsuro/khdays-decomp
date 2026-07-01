extern void func_0202a7dc(void *arg);
extern void func_ov022_02091228(void *arg);
extern void NNSi_FndFreeFromDefaultHeap(void *arg);
extern int data_ov047_020b4380;

asm void func_ov047_020b38b4(void *arg)
{
    stmfd   sp!, {r4, lr}
    ldr     r1, =data_ov047_020b4380
    mov     r4, r0
    ldr     r0, [r1]
    add     r0, r0, #0x64
    add     r0, r0, #0x2c00
    bl      func_0202a7dc
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    ldmfd   sp!, {r4, pc}
}
