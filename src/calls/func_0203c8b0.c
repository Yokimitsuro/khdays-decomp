extern void func_0201f390(int lock);

asm void func_0203c8b0(void *self)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4, #0x7c]
    cmp   r0, #0
    ldmeqia sp!, {r4, pc}
    mov   r0, #0
    bl    func_0201f390
    ldr   r1, [r4, #0x7c]
    mov   r0, r4
    blx   r1
    mov   r0, #1
    bl    func_0201f390
    ldmia sp!, {r4, pc}
}
