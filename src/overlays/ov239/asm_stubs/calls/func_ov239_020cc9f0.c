extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_0203c634(void);

asm void func_ov239_020cc9f0(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a07000
    dcd     0xe5974004
    dcd     0xe1a05003
    dcd     0xe5940000
    dcd     0xe1a06002
    dcd     0xe1a02005
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe1a01006
    dcd     0xe5900398
    dcd     0xe1a02005
    bl      func_ov107_020c9ee8
    dcd     0xe1d712d0
    dcd     0xe59d2018
    dcd     0xe1a00007
    bl      func_0203c634
    dcd     0xe8bd80f8
}
