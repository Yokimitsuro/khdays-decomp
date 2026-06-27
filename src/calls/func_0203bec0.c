extern int func_0202aee0(void *p);

asm int func_0203bec0(void *self, int idx)
{
    stmdb sp!, {r3, lr}
    ldr r3, [r0, #0x8c]
    mov r2, r1, lsl #1
    ldrsh r2, [r3, r2]
    cmp r2, #0
    moveq r0, #0
    ldmeqia sp!, {r3, pc}
    ldr r0, [r0, #0x88]
    bl  func_0202aee0
    ldmia sp!, {r3, pc}
}
