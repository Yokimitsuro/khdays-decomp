/* KBEC/CEBK chunk opener: scans for fourcc 0x4345424b, then runs handler func_020118ec. */
extern void *func_02011aa0(void *a, int magic);
extern void func_020118ec(void *p);

asm void func_02011888(void *a, void **out)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r1
    ldr r1, =0x4345424b
    bl func_02011aa0
    movs r4, r0
    moveq r0, #0
    streq r0, [r5]
    ldmeqia sp!, {r3, r4, r5, pc}
    add r0, r4, #8
    bl func_020118ec
    add r0, r4, #8
    str r0, [r5]
    mov r0, #1
    ldmia sp!, {r3, r4, r5, pc}
}
