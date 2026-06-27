extern void func_02029250(void *cmd, void *out);

asm void func_0202b3b0(void *self)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4]
    tst   r0, #8
    ldmeqia sp!, {r4, pc}
    tst   r0, #0x10
    bne   clear
    ldr   r0, [r4, #0x10c]
    add   r1, r4, #0x110
    ldr   r0, [r0, #4]
    ldr   r0, [r0]
    bl    func_02029250
clear:
    ldr   r0, [r4]
    bic   r0, r0, #8
    str   r0, [r4]
    ldmia sp!, {r4, pc}
}
