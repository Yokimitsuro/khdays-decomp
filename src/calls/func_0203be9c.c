extern int func_01fff774();

asm void func_0203be9c(void *p, int idx)
{
    stmdb sp!, {r3, lr}
    ldr   ip, [r0, #0x8c]
    mov   r3, r1, lsl #1
    ldrsh r3, [ip, r3]
    cmp   r3, #0
    ldmeqia sp!, {r3, pc}
    ldr   r0, [r0, #0x88]
    bl    func_01fff774
    ldmia sp!, {r3, pc}
}
