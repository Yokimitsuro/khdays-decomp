extern void func_ov063_020b6290(void);
extern void func_ov063_020b62a4(void);
extern void func_ov063_020b7910(void);

asm void func_ov063_020b622c(void)
{
    dcd     0xe92d4008
    dcd     0xe28020a8
    dcd     0xe3510022
    dcd     0xe3a00000
    dcd     0x0a000002
    dcd     0xe3510023
    dcd     0x0a000005
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01022
    bl      func_ov063_020b7910
    dcd     0xe59f0014
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01023
    bl      func_ov063_020b7910
    dcd     0xe59f0004
    dcd     0xe8bd8008
    dcd     func_ov063_020b6290
    dcd     func_ov063_020b62a4
}
