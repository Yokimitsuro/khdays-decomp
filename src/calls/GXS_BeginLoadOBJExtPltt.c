extern int GX_DisableBankForSubOBJExtPltt(void);
extern int data_020446f0[];

asm void GXS_BeginLoadOBJExtPltt(void)
{
    stmdb sp!, {r3, lr}
    bl GX_DisableBankForSubOBJExtPltt
    ldr r1, =data_020446f0
    str r0, [r1, #0x18]
    ldmia sp!, {r3, pc}
}
