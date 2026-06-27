extern void MI_CpuFill8(void *dst, int val, int n);
extern void *func_0201ef9c(int a, int b);

asm void func_ov010_0204cac0(int **out, int a)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r1
    mov     r1, #0
    mov     r2, #0xc
    mov     r5, r0
    bl      MI_CpuFill8
    mov     r0, r4
    mov     r1, #0xe
    bl      func_0201ef9c
    str     r0, [r5]
    ldr     r2, [r0]
    ldr     r1, [r0, #4]
    str     r1, [r5, #4]
    ldr     r1, [r5]
    add     r1, r1, r2
    str     r1, [r5, #8]
    ldmfd   sp!, {r3, r4, r5, pc}
}
