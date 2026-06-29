extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_ov121_020cf918(void);

asm void func_ov121_020cf8ac(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01007
    dcd     0xe594c000
    dcd     0xe3a02000
    dcd     0xe1dc36b0
    dcd     0xe1a00803
    dcd     0xe1a00c20
    dcd     0xe3800040
    dcd     0xe3c33cff
    dcd     0xe1a00c00
    dcd     0xe1830820
    dcd     0xe1cc06b0
    dcd     0xe5940000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe59003a0
    dcd     0xe3a02000
    bl      func_ov107_020c9ee8
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov121_020cf918
}
