extern void func_0202a440(void *p);
extern void func_0201f6b0(void *p);
extern void func_0201f5ac(void *p);
extern void func_0202a6d8(void *self);

asm void func_0202a7dc(void *self)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    add   r0, r4, #0xe0
    bl    func_0202a440
    ldr   r0, [r4, #0x74]
    cmp   r0, #0
    beq   skip
    bl    func_0201f6b0
    ldr   r0, [r4, #0x74]
    bl    func_0201f5ac
skip:
    mov   r1, #0
    mov   r0, r4
    str   r1, [r4, #0x74]
    bl    func_0202a6d8
    ldmia sp!, {r4, pc}
}
