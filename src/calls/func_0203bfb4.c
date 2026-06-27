extern void func_0203c83c(int a, void *b);
extern int *func_01fffca8(void *p, int a, int b);

asm int func_0203bfb4(void *p, int arg1)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    mov   r4, r1
    mov   r0, r4
    mov   r1, r5
    bl    func_0203c83c
    add   r0, r5, #0x88
    mov   r1, #4
    mov   r2, #0x64
    bl    func_01fffca8
    str   r4, [r0]
    mov   r0, #0
    ldmia sp!, {r3, r4, r5, pc}
}
