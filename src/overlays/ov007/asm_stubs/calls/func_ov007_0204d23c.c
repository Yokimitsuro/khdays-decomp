extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202fa20(void *p);
extern void func_0202f9f8(void *p);
extern int func_ov007_0204cf7c(void);
extern int data_0204c190;
extern int func_ov007_0204d2d0(void);

asm int func_ov007_0204d23c(void)
{
    stmfd   sp!, {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, [r4, #0x20]
    mov     r1, #0
    add     r0, r0, #1
    str     r0, [r4, #0x20]
    cmp     r0, #8
    blt     _lt
    ldr     r2, =0x05000002
    add     r0, r4, #0x30
    strh    r1, [r2]
    str     r1, [r4, #0x20]
    str     r1, [r4, #0x70]
    bl      func_0202fa20
    add     r0, r4, #0x30
    bl      func_0202f9f8
    ldr     r1, =func_ov007_0204cf7c
    b       _end
_lt:
    mov     r0, r0, lsl #2
    rsb     r3, r0, #0x20
    orr     r2, r3, r3, lsl #5
    ldr     r0, =0x05000002
    orr     r2, r2, r3, lsl #10
    strh    r2, [r0]
_end:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #8
    movne   r0, #0
    ldrne   r1, =func_ov007_0204d2d0
    strne   r0, [r4, #0x20]
    mov     r0, r1
    ldmfd   sp!, {r4, pc}
}
