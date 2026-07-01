extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204d364(void *p);
extern void func_0202f9ec(void *p);
extern void func_0202f818(void *p);
extern void func_02032428(void *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_02024fd4(void *p);
extern int data_ov007_0204d3c0;
extern int data_ov007_0204d420;

asm void func_ov007_0204ce30(void)
{
    stmfd   sp!, {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    add     r0, r4, #8
    bl      func_ov007_0204d364
    add     r0, r4, #0x30
    bl      func_0202f9ec
    add     r0, r4, #0x24
    bl      func_0202f818
    add     r0, r4, #0x7c
    add     r0, r0, #0x1000
    bl      func_02032428
    ldr     r0, [r4, #4]
    bl      NNSi_FndFreeFromDefaultHeap
    ldr     r0, [r4]
    bl      func_02024fd4
    ldr     r1, =data_ov007_0204d3c0
    mvn     r3, #0
    ldr     r0, =data_ov007_0204d420
    mov     r2, #0
    str     r3, [r1]
    str     r2, [r0]
    ldmfd   sp!, {r4, pc}
}
