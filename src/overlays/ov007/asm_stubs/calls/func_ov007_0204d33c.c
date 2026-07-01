extern void MI_CpuFill8(void *dst, int val, int n);
extern void *func_0201ef9c(int a, int b);

asm void func_ov007_0204d33c(int **out, int a)
{
    push    {r3, r4, r5, lr}
    add     r5, r1, #0
    mov     r1, #0
    mov     r2, #0xc
    add     r4, r0, #0
    bl      MI_CpuFill8
    add     r0, r5, #0
    mov     r1, #0xe
    bl      func_0201ef9c
    str     r0, [r4]
    ldr     r1, [r0, #0]
    ldr     r0, [r0, #4]
    str     r0, [r4, #4]
    ldr     r0, [r4, #0]
    add     r0, r0, r1
    str     r0, [r4, #8]
    pop     {r3, r4, r5, pc}
}
