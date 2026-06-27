extern void *func_0203d15c(int);
extern void func_0203bf60(void);

asm void *func_0203bf44(void)
{
    stmdb sp!, {r4, lr}
    mov r0, #0xb4
    bl func_0203d15c
    mov r4, r0
    bl func_0203bf60
    mov r0, r4
    ldmia sp!, {r4, pc}
}
