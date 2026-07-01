extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02032710(int r0, int r1, int r2);
extern void func_ov007_0204ce94(void *p);
extern void func_02033b24(int r0, int r1);
extern void func_0203255c(int r0);
extern int data_0204c190;
extern int func_ov007_0204d2d0(void);
extern int func_ov007_0204d23c(void);

asm int func_ov007_0204d170(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, [r4, #0x20]
    mov     r5, #0
    cmp     r0, #0
    bne     _skip1
    add     r1, r4, #0x5000
    add     r0, r4, #0x7c
    ldr     r1, [r1, #0xab4]
    add     r0, r0, #0x1000
    mov     r2, #1
    bl      func_02032710
    ldr     r0, [r4, #0x20]
    add     r0, r0, #1
    str     r0, [r4, #0x20]
_skip1:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #1
    beq     _skip2
    add     r1, r4, #0x5000
    add     r0, r4, #0x7c
    ldr     r1, [r1, #0xab4]
    add     r0, r0, #0x1000
    mov     r2, #0
    bl      func_02032710
    mov     r1, #0
    mov     r0, r4
    str     r1, [r4, #0x20]
    bl      func_ov007_0204ce94
    ldrh    r0, [r4, #0x7c]
    mov     r1, #0xa
    cmp     r0, #0
    ldreq   r5, =func_ov007_0204d2d0
    mov     r0, #0
    ldrne   r5, =func_ov007_0204d23c
    bl      func_02033b24
_skip2:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #8
    movne   r0, #0
    strne   r0, [r4, #0x20]
    add     r0, r4, #0x7c
    add     r0, r0, #0x1000
    ldrne   r5, =func_ov007_0204d2d0
    bl      func_0203255c
    mov     r0, r5
    ldmfd   sp!, {r3, r4, r5, pc}
}
