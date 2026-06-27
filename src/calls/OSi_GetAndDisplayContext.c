extern void OSi_SetExContext(void);
extern void func_0200302c(void);

asm void OSi_GetAndDisplayContext(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext
    bl func_0200302c
    ldmia sp!, {r0, lr}
    bx lr
}
