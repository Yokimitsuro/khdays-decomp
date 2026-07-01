extern void func_02008158(unsigned char arg);

asm int func_0201a284(void *self)
{
    stmdb sp!, {r3, lr}
    ldr r3, [r0]
    cmp r3, #0
    moveq r0, #0
    ldmeqia sp!, {r3, pc}
    ldr r0, [r0]
    ldrb r0, [r0, #0x3c]
    bl func_02008158
    mov r0, #1
    ldmia sp!, {r3, pc}
}
