extern void func_0202e474(void);
extern void *data_020475d0;

asm void func_0202e4f4(void)
{
    stmdb sp!, {r3, lr}
    sub sp, sp, #0x188
    ldr r2, =data_020475d0
    ldr r3, [r2]
    cmp r3, #0
    bne nonzero
    add r3, sp, #0
    str r3, [r2]
    bl func_0202e474
    ldr r0, =data_020475d0
    mov r1, #0
    str r1, [r0]
    add sp, sp, #0x188
    ldmia sp!, {r3, pc}
nonzero:
    bl func_0202e474
    add sp, sp, #0x188
    ldmia sp!, {r3, pc}
}
