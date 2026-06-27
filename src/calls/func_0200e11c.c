extern void func_0200de48(void *, int);
extern void func_02001780(void *);

asm void func_0200e11c(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    mov r1, #1
    bl func_0200de48
    mov r0, r4
    bl func_02001780
    ldmia sp!, {r4, pc}
}
