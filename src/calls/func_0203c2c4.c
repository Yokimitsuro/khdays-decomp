extern void func_0202a7dc(void *p);
extern void func_0203d194(void *p);
extern void func_0203c900(void *self);

asm void func_0203c2c4(void *self)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4, #0x88]
    bl    func_0202a7dc
    ldr   r0, [r4, #0x88]
    bl    func_0203d194
    ldr   r0, [r4, #0x90]
    cmp   r0, #0
    beq   skip
    bl    func_0203d194
skip:
    mov   r1, #0
    str   r1, [r4, #0x90]
    mov   r0, r4
    str   r1, [r4, #0x8c]
    bl    func_0203c900
    ldmia sp!, {r4, pc}
}
