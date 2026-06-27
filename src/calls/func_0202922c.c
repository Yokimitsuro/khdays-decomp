extern int func_02028ff4(void *a, void *b, void *c);

asm void func_0202922c(void *self, void *arg)
{
    stmdb sp!, {r3, lr}
    mov   r3, r0
    ldr   r0, [r3, #0x9c]
    mov   r2, r1
    cmp   r0, #0
    ldmeqia sp!, {r3, pc}
    add   r1, r3, #0x84
    bl    func_02028ff4
    ldmia sp!, {r3, pc}
}
