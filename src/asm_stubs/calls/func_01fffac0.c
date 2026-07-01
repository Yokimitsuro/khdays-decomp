extern int func_01fffaf4(void *p);

asm void func_01fffac0(void *self)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    ldr r0, [r4, #0x18]
    bl func_01fffaf4
    cmp r0, #0
    ldmeqia sp!, {r4, pc}
    ldr r2, [r4, #0x1c]
    mov r1, #0xc
    eor r2, r2, #1
    mla r1, r2, r1, r4
    str r2, [r4, #0x1c]
    str r1, [r4, #0x18]
    ldmia sp!, {r4, pc}
}
