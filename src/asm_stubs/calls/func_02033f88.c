extern void func_0201cac0(void *p, int x);
extern int *data_0204c234;

asm void func_02033f88(int idx)
{
    stmdb sp!, {r3, lr}
    ldr   r2, =data_0204c234
    ldr   r3, =0xb44bc
    ldr   ip, [r2]
    mov   r2, #0
    add   r3, ip, r3
    add   r0, r3, r0, lsl #2
    bl    func_0201cac0
    ldmia sp!, {r3, pc}
}
