extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov182_020d0484(void);

asm void func_ov182_020d0428(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01011
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940078
    dcd     0xe59f2030
    dcd     0xe2600000
    dcd     0xe5840078
    dcd     0xe5940080
    dcd     0xe2600000
    dcd     0xe5840080
    dcd     0xe594007c
    dcd     0xe3500000
    dcd     0xc3a00000
    dcd     0xc584007c
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov182_020d0484
}
