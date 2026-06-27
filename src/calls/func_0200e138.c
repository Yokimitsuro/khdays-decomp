extern void func_0200179c(void *);
extern void func_0200decc(void *, int);

asm void func_0200e138(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl func_0200179c
    mov r0, r4
    mov r1, #1
    bl func_0200decc
    ldmia sp!, {r4, pc}
}
