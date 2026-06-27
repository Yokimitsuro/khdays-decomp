extern void func_0201acec(void *);

asm void func_0201ac34(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r1, [r0, #0x24]
    mov r1, r1, lsl #0x1f
    movs r1, r1, asr #0x1f
    ldmeqia sp!, {r3, pc}
    bl func_0201acec
    ldmia sp!, {r3, pc}
}
