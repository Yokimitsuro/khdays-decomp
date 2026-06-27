extern void FS_EndOverlay(void);

asm int FS_UnloadOverlayImage(void)
{
    stmdb sp!, {r3, lr}
    bl FS_EndOverlay
    mov r0, #1
    ldmia sp!, {r3, pc}
}
