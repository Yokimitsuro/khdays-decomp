extern void func_01ff88c4(void);

asm int func_0200a1a8(void)
{
    stmdb sp!, {r3, lr}
    mov r0, r2
    mov r2, r3
    bl func_01ff88c4
    mov r0, #0
    ldmia sp!, {r3, pc}
}
