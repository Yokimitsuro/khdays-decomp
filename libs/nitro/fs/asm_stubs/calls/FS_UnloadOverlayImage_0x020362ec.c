extern void func_0203617c(void);

asm int FS_UnloadOverlayImage_0x020362ec(void)
{
    stmdb sp!, {r3, lr}
    bl func_0203617c
    mov r0, #1
    ldmia sp!, {r3, pc}
}
