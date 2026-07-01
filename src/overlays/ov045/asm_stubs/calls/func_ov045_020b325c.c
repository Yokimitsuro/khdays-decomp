extern void *NNSi_FndGetCurrentRootHeap();
extern void func_0202a7dc(void *);
extern void func_ov045_020b4178(void *);
extern void func_ov022_0209fab4(void *);
extern void *data_ov045_020b4c20;

asm void func_ov045_020b325c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, =0x2c2c
    ldr     r1, [r4, r0]
    cmp     r1, #0
    beq     _skip
    add     r0, r0, #4
    add     r0, r4, r0
    bl      func_0202a7dc
    ldr     r0, =0x2c2c
    mov     r1, #0
    str     r1, [r4, r0]
_skip:
    add     r0, r4, #0
    bl      func_ov045_020b4178
    add     r0, r4, #0
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov045_020b4c20
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
}
