extern void func_02003c54(int);
extern void func_02003f84(int);

asm void func_02004608(void)
{
    stmdb sp!, {r3, lr}
    mov r0, #3
    bl func_02003c54
    mov r0, #0
    bl func_02003f84
    ldmia sp!, {r3, pc}
}
