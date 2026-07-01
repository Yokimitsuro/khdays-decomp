extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(void *a, void *b);
extern void func_ov034_020b510c(void *arg);
extern void func_ov022_0209fab4(void *arg);
extern int data_ov034_020b5660;

asm void func_ov034_020b3268(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, =0x2c2c
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    mov     r0, #0xb2
    mov     r1, #0x91
    lsl     r0, r0, #6
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    add     r0, r4, #0
    bl      func_ov034_020b510c
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov034_020b5660
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
}
