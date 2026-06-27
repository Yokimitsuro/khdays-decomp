extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202fa38(int r0, int r1, int r2, int r3, int s0, int s1);
extern void func_0202f9f8(void *p);
extern int func_ov007_0204d0ec(void);
extern int data_0204c190;
extern int func_ov007_0204d2d0(void);

asm int func_ov007_0204cf7c(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    sub     sp, sp, #8
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, [r4, #0x20]
    mov     r5, #0
    cmp     r0, #0
    bne     _skip1
    ldr     r2, =0x7fff
    ldr     r1, =0x05000002
    mov     r0, #0x14
    strh    r2, [r1]
    strh    r5, [r1, #2]
    str     r0, [sp]
    add     r0, r4, #0x7c
    str     r0, [sp, #4]
    ldr     r1, [r4, #0x70]
    mov     r0, #0x12
    mul     r2, r1, r0
    add     r0, r4, #0x30
    add     r2, r2, #0xe
    mov     r1, #0x80
    mov     r3, #2
    bl      func_0202fa38
    add     r0, r4, #0x30
    bl      func_0202f9f8
_skip1:
    ldr     r0, [r4, #0x20]
    add     r2, r0, #1
    str     r2, [r4, #0x20]
    cmp     r2, #0x20
    blt     _branch2
    mov     r0, #0x14
    str     r0, [sp]
    add     r0, r4, #0x7c
    str     r0, [sp, #4]
    ldr     r1, [r4, #0x70]
    mov     r0, #0x12
    mul     r2, r1, r0
    add     r0, r4, #0x30
    add     r2, r2, #0xe
    mov     r1, #0x80
    mov     r3, #1
    bl      func_0202fa38
    add     r0, r4, #0x30
    bl      func_0202f9f8
    mov     r0, #0
    str     r0, [r4, #0x20]
    ldr     r5, =func_ov007_0204d0ec
    b       _skip2
_branch2:
    orr     r1, r2, r2, lsl #5
    ldr     r0, =0x05000004
    orr     r1, r1, r2, lsl #10
    strh    r1, [r0]
_skip2:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #1
    beq     _end
    ldr     r0, [r4, #0x20]
    cmp     r0, #0x20
    bge     _skip3
    mov     r0, #0x14
    str     r0, [sp]
    add     r0, r4, #0x7c
    str     r0, [sp, #4]
    ldr     r1, [r4, #0x70]
    mov     r0, #0x12
    mul     r2, r1, r0
    add     r0, r4, #0x30
    add     r2, r2, #0xe
    mov     r1, #0x80
    mov     r3, #1
    bl      func_0202fa38
    add     r0, r4, #0x30
    bl      func_0202f9f8
_skip3:
    mov     r0, #0xf
    ldr     r5, =func_ov007_0204d0ec
    str     r0, [r4, #0x20]
_end:
    ldr     r0, =data_0204c190
    ldrh    r0, [r0]
    tst     r0, #8
    movne   r0, #0
    ldrne   r5, =func_ov007_0204d2d0
    strne   r0, [r4, #0x20]
    mov     r0, r5
    add     sp, sp, #8
    ldmfd   sp!, {r3, r4, r5, pc}
}
