extern void func_ov144_020cca50(void);
extern void func_ov107_020c9264(void);

asm void func_ov144_020cd9ac(void)
{
    dcd     0xe92d4010
    dcd     0xe5904004
    dcd     0xe1a00004
    bl      func_ov144_020cca50
    dcd     0xe5941000
    dcd     0xe5910384
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8010
    dcd     0xe594004c
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe1a00001
    dcd     0xe3a01000
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe8bd8010
    dcd     0xe59123a4
    dcd     0xe3520000
    dcd     0x15940004
    dcd     0x13500000
    dcd     0x08bd8010
    dcd     0xe5d001b4
    dcd     0xe12fff32
    dcd     0xe8bd8010
}
