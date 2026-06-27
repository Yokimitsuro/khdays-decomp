extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov053_020b5aac(void *arg);
extern void func_ov053_020b78b4(void *arg);
extern void func_ov022_020a4798(void *arg, int x, int y);
extern void func_ov022_0209fb24(void);

asm void func_ov053_020b5a34(void *arg)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, =0x2e1c
    mov     r1, #0
    str     r1, [r4, r0]
    add     r0, r5, #0
    bl      func_ov053_020b5aac
    add     r0, r4, #0
    mov     r1, #0x45
    mov     r2, #0xc6
    bl      func_ov022_020a4798
    add     r0, r4, #0
    bl      func_ov053_020b78b4
    ldr     r0, =func_ov022_0209fb24
    pop     {r3, r4, r5, pc}
}
