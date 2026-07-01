extern int GX_DisableBankForSubBGExtPltt(void);
extern int data_020446f0[];

asm void GXS_BeginLoadBGExtPltt(void)
{
    stmdb sp!, {r3, lr}
    bl GX_DisableBankForSubBGExtPltt
    ldr r1, =data_020446f0
    str r0, [r1]
    ldmia sp!, {r3, pc}
}
