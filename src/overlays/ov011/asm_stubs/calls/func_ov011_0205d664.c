extern void WM_EndKeySharing_0x02032444(void);
extern void func_0203281c(void);
extern void func_02032710(void);

asm void func_ov011_0205d664(void)
{
    dcd     0xe92d4038
    dcd     0xe3a02000
    dcd     0xe1a05000
    bl      WM_EndKeySharing_0x02032444
    dcd     0xe1a04000
    dcd     0xe1a00005
    dcd     0xe1a01004
    dcd     0xe3a02000
    bl      func_0203281c
    dcd     0xe1a00005
    dcd     0xe1a01004
    dcd     0xe3a02000
    bl      func_02032710
    dcd     0xe1a00004
    dcd     0xe8bd8038
}
