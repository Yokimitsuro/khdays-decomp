extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204d170(void);
extern int func_ov007_0204cf7c(void);
extern int data_0204c190;
extern int func_ov007_0204d2d0(void);

asm int func_ov007_0204d0ec(void)
{
    stmfd   sp!, {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r1, [r4, #0x20]
    mov     r2, #0
    add     r1, r1, #1
    str     r1, [r4, #0x20]
    cmp     r1, #0xf
    blt     _skip
    bl      func_ov007_0204ce94
    ldrh    r0, [r4, #0x7c]
    cmp     r0, #0
    mov     r0, #0
    streq   r0, [r4, #0x20]
    ldreq   r2, =func_ov007_0204d170
    beq     _skip
    ldr     r1, [r4, #0x70]
    ldr     r2, =func_ov007_0204cf7c
    add     r1, r1, #1
    str     r1, [r4, #0x70]
    str     r0, [r4, #0x20]
_skip:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #8
    movne   r0, #0
    ldrne   r2, =func_ov007_0204d2d0
    strne   r0, [r4, #0x20]
    mov     r0, r2
    ldmfd   sp!, {r4, pc}
}
