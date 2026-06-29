extern void func_ov099_020bb0d0(void);
extern void func_ov099_020bb828(void);
extern void func_ov099_020bb8d0(void);

asm void func_ov099_020bc7a4(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe351002e
    dcd     0xe5943db4
    dcd     0x0a000004
    dcd     0xe351002f
    dcd     0x0a000007
    dcd     0xe3510030
    dcd     0x0a00000c
    dcd     0xe8bd8010
    dcd     0xe59326bc
    dcd     0xe1520001
    dcd     0x08bd8010
    bl      func_ov099_020bb0d0
    dcd     0xe8bd8010
    dcd     0xe59326bc
    dcd     0xe1520001
    dcd     0x08bd8010
    dcd     0xe3a01001
    dcd     0xe5841008
    bl      func_ov099_020bb8d0
    dcd     0xe8bd8010
    dcd     0xe3a02001
    dcd     0xe5842000
    dcd     0xe59326bc
    dcd     0xe1520001
    dcd     0x08bd8010
    bl      func_ov099_020bb8d0
    dcd     0xe1a00004
    bl      func_ov099_020bb828
    dcd     0xe8bd8010
}
