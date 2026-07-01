extern void func_0200dce0(void);
extern void *func_0200d674(int a, void *cb, int c);
extern void func_0200dcf0(void);
extern void *data_02046438;

asm void *func_0200d6e8(int arg0)
{
    stmdb sp!, {r3, lr}
    ldr   r1, =func_0200dce0
    mov   r2, #0
    bl    func_0200d674
    ldr   r1, =data_02046438
    cmp   r0, #0
    str   r0, [r1, #0x2c]
    bne   _skip
    bl    func_0200dcf0
_skip:
    ldr   r0, =data_02046438
    ldr   r0, [r0, #0x2c]
    ldmia sp!, {r3, pc}
}
