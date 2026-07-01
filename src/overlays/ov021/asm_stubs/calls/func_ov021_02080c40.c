extern char data_ov021_02080f40[];
extern void func_ov002_02076a80(void);

asm void func_ov021_02080c40(void)
{
    dcd     0xe92d40f8
    dcd     0xe59f4048
    dcd     0xe1a07000
    dcd     0xe5940000
    dcd     0xe3500000
    dcd     0x08bd80f8
    dcd     0xe1d015b0
    dcd     0xe3a06000
    dcd     0xe3510000
    dcd     0xd8bd80f8
    dcd     0xe3a0594b
    dcd     0xe1a01006
    bl      func_ov002_02076a80
    dcd     0xe1500007
    dcd     0x158052b8
    dcd     0xe5940000
    dcd     0xe2866001
    dcd     0xe1d015b0
    dcd     0xe1560001
    dcd     0xbafffff6
    dcd     0xe8bd80f8
    dcd     data_ov021_02080f40
}
