extern void func_ov044_020b3b30(void);
extern void func_ov044_020b4288(void);
extern void func_ov044_020b4330(void);

asm void func_ov044_020b5204(void)
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
    bl      func_ov044_020b3b30
    dcd     0xe8bd8010
    dcd     0xe59326bc
    dcd     0xe1520001
    dcd     0x08bd8010
    dcd     0xe3a01001
    dcd     0xe5841008
    bl      func_ov044_020b4330
    dcd     0xe8bd8010
    dcd     0xe3a02001
    dcd     0xe5842000
    dcd     0xe59326bc
    dcd     0xe1520001
    dcd     0x08bd8010
    bl      func_ov044_020b4330
    dcd     0xe1a00004
    bl      func_ov044_020b4288
    dcd     0xe8bd8010
}
