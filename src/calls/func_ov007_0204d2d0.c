extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int);
extern int func_ov007_0204d31c(void);

asm int func_ov007_0204d2d0(void)
{
    stmfd   sp!, {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    ldr     r1, [r0, #0x20]
    mov     r4, #0
    add     r1, r1, #1
    str     r1, [r0, #0x20]
    cmp     r1, #0x20
    blt     _lt
    sub     r0, r4, #0x10
    bl      func_0201e374
    ldr     r4, =func_ov007_0204d31c
    b       _end
_lt:
    rsb     r0, r1, #0
    add     r0, r0, r0, lsr #31
    mov     r0, r0, asr #1
    bl      func_0201e374
_end:
    mov     r0, r4
    ldmfd   sp!, {r4, pc}
}
