extern void func_0201e144(void *p, int b);

asm void func_0201a124(void *self, int arg1)
{
    stmdb sp!, {r3, lr}
    ldr r3, [r0]
    cmp r3, #0
    ldrne r3, [r0]
    ldrneb r0, [r3, #0x2c]
    cmpne r0, #2
    ldmeqia sp!, {r3, pc}
    add r0, r3, #0x1c
    mov r1, r1, lsl #8
    bl func_0201e144
    ldmia sp!, {r3, pc}
}
