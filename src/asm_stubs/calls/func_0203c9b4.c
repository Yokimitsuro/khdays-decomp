extern void func_0202f188(void *);

asm void func_0203c9b4(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl func_0202f188
    ldrb r0, [r4, #0x28]
    bic r0, r0, #1
    strb r0, [r4, #0x28]
    ldmia sp!, {r4, pc}
}
