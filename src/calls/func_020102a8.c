extern void func_02010204(void *);
extern void func_020100c8(void *, void *);

asm void func_020102a8(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl func_02010204
    mov r1, r4
    bl func_020100c8
    ldmia sp!, {r4, pc}
}
