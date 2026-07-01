extern void func_02029158(void *);

asm void func_02029250(void *object, void *arg)
{
    stmdb sp!, {r3, lr}
    ldr r0, [r0, #0x9c]
    cmp r0, #0
    ldmeqia sp!, {r3, pc}
    mov r0, r1
    bl func_02029158
    ldmia sp!, {r3, pc}
}
