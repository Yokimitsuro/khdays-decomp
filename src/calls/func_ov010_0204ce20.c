extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_0203602c(int, int *);
extern void func_0201e374(int);
extern void func_0201e3cc(int);

asm void func_ov010_0204ce20(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    add     r1, sp, #0
    add     r0, r4, #0x58
    bl      func_0203602c
    ldr     r0, [sp]
    mov     r5, r0, asr #0xc
    mov     r0, r5
    bl      func_0201e374
    mov     r0, r5
    bl      func_0201e3cc
    ldr     r0, [r4, #0x70]
    mov     r0, r0, lsl #0x1d
    mov     r0, r0, lsr #0x1f
    ldmfd   sp!, {r3, r4, r5, pc}
}
