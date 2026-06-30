extern void GXS_LoadBG3Scr(void);
extern void GXS_LoadBG3Scr_0x020074cc(void);
extern void GXS_LoadBG3Scr_0x0200758c(void);

asm void func_ov012_0205b32c(void)
{
    dcd     0xe92d4008
    dcd     0xe1d230b6
    dcd     0xe3a0100c
    dcd     0xe1d220b8
    dcd     0xe0200193
    dcd     0xe2800902
    dcd     0xe3520000
    dcd     0xe5900c00
    dcd     0x0a000004
    dcd     0xe3520001
    dcd     0x0a000007
    dcd     0xe3520002
    dcd     0x0a00000a
    dcd     0xea00000d
    dcd     0xe5902008
    dcd     0xe280000c
    dcd     0xe3a01000
    bl      GXS_LoadBG3Scr
    dcd     0xea000008
    dcd     0xe5902008
    dcd     0xe280000c
    dcd     0xe3a01000
    bl      GXS_LoadBG3Scr_0x020074cc
    dcd     0xea000003
    dcd     0xe5902008
    dcd     0xe280000c
    dcd     0xe3a01000
    bl      GXS_LoadBG3Scr_0x0200758c
    dcd     0xe3a00001
    dcd     0xe8bd8008
}
