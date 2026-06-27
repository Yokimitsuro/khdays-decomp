extern void *func_01fffd70(void *p);
extern void *func_01fffd8c(void *p);
extern void func_0203c8b0(void *p);

asm void func_0203c148(void *self)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    add r0, r4, #0x88
    bl func_01fffd70
    cmp r0, #0
    ldmeqia sp!, {r4, pc}
loop:
    ldr r0, [r0]
    bl func_0203c8b0
    add r0, r4, #0x88
    bl func_01fffd8c
    cmp r0, #0
    bne loop
    ldmia sp!, {r4, pc}
}
