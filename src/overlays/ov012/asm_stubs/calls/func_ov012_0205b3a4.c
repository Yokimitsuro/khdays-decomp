extern void GX_LoadBGPltt(void);

asm void func_ov012_0205b3a4(void)
{
    dcd     0xe92d4008
    dcd     0xe1d230b6
    dcd     0xe3a0200c
    dcd     0xe3a01000
    dcd     0xe0200293
    dcd     0xe2800902
    dcd     0xe5902c08
    dcd     0xe592000c
    dcd     0xe5922008
    bl      GX_LoadBGPltt
    mov r0, #1
    dcd     0xe8bd8008
}
