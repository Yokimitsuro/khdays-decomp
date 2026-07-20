extern void GX_LoadBG0Scr(void);
extern void GX_LoadBG1Scr(void);
extern void GX_LoadBG2Scr(void);

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
    bl      GX_LoadBG0Scr
    dcd     0xea000008
    dcd     0xe5902008
    dcd     0xe280000c
    dcd     0xe3a01000
    bl      GX_LoadBG1Scr
    dcd     0xea000003
    dcd     0xe5902008
    dcd     0xe280000c
    dcd     0xe3a01000
    bl      GX_LoadBG2Scr
    mov r0, #1
    dcd     0xe8bd8008
}
