extern void GXS_LoadBG3Char(void);
extern void GXS_LoadBG3Char_0x020077cc(void);
extern void GXS_LoadBG3Char_0x0200788c(void);

asm void func_ov012_0205b2a4(void)
{
    dcd     0xe92d4010
    dcd     0xe1d230b6
    dcd     0xe1d210b8
    dcd     0xe1a04000
    dcd     0xe3a0000c
    dcd     0xe0204093
    dcd     0xe2800902
    dcd     0xe3510000
    dcd     0xe5902c04
    dcd     0x0a000004
    dcd     0xe3510001
    dcd     0x0a000007
    dcd     0xe3510002
    dcd     0x0a00000a
    dcd     0xea00000d
    dcd     0xe5920014
    dcd     0xe5922010
    dcd     0xe3a01000
    bl      GXS_LoadBG3Char
    dcd     0xea000008
    dcd     0xe5920014
    dcd     0xe5922010
    dcd     0xe3a01000
    bl      GXS_LoadBG3Char_0x020077cc
    dcd     0xea000003
    dcd     0xe5920014
    dcd     0xe5922010
    dcd     0xe3a01000
    bl      GXS_LoadBG3Char_0x0200788c
    dcd     0xe2840902
    dcd     0xe3e0100f
    dcd     0xe5801bf4
    mov r0, #1
    dcd     0xe8bd8010
}
