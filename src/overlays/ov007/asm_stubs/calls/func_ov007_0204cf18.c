extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204cf7c(void);

asm int func_ov007_0204cf18(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, [r4, #0x20]
    mov     r5, #0
    add     r0, r0, #1
    str     r0, [r4, #0x20]
    cmp     r0, #0x20
    blt     _lt
    mov     r0, r5
    bl      func_0201e374
    mov     r1, r5
    str     r1, [r4, #0x20]
    mov     r0, r4
    str     r1, [r4, #0x70]
    bl      func_ov007_0204ce94
    ldr     r5, =func_ov007_0204cf7c
    b       _end
_lt:
    add     r0, r0, r0, lsr #31
    mov     r0, r0, asr #1
    sub     r0, r0, #0x10
    bl      func_0201e374
_end:
    mov     r0, r5
    ldmfd   sp!, {r3, r4, r5, pc}
}
