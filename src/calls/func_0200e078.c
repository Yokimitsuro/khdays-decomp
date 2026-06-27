extern int func_0200e068(void);
extern void func_02003c38(void);

asm void func_0200e078(void)
{
    stmdb sp!, {r3, lr}
    bl func_0200e068
    cmp r0, #0
    ldmneia sp!, {r3, pc}
    bl func_02003c38
    ldmia sp!, {r3, pc}
}
