extern void *func_02011aa0(void *a, int magic);
extern void func_020119c4(void *p);

asm void func_02011988(void *a, void **out)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r1
    ldr r1, =0x43484152
    bl func_02011aa0
    movs r4, r0
    moveq r0, #0
    streq r0, [r5]
    ldmeqia sp!, {r3, r4, r5, pc}
    add r0, r4, #8
    bl func_020119c4
    add r0, r4, #8
    str r0, [r5]
    mov r0, #1
    ldmia sp!, {r3, r4, r5, pc}
}
