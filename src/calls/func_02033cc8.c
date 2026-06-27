extern int  func_0201a210(int x);
extern int  func_0201a0a8(void);
extern char data_0204c234[];

asm int func_02033cc8(void)
{
    stmdb sp!, {r3, lr}
    ldr   r1, =data_0204c234
    ldr   r0, =0x000b44c4
    ldr   r1, [r1]
    add   r0, r1, r0
    bl    func_0201a210
    cmp   r0, #0
    blt   fail
    bl    func_0201a0a8
    cmp   r0, #0
    bne   ok
fail:
    mov   r0, #0
    ldmia sp!, {r3, pc}
ok:
    mov   r0, #1
    ldmia sp!, {r3, pc}
}
