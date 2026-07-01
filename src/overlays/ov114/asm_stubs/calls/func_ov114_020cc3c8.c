extern void func_ov107_020cb100(void);
extern void func_ov107_020c7ca4(void);

asm void func_ov114_020cc3c8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5d401c4
    dcd     0xe310000a
    dcd     0x0a00000d
    dcd     0xe2840c01
    dcd     0xe1d02cd7
    dcd     0xe3e01000
    dcd     0xe1520001
    dcd     0x1a000008
    dcd     0xe1d00cd6
    dcd     0xe3500000
    dcd     0x13500001
    dcd     0x13500003
    dcd     0x13500005
    dcd     0x1350000b
    dcd     0x13500007
    dcd     0x13a00005
    dcd     0x15c401c7
    dcd     0xe2840c01
    dcd     0xe1d00cd6
    dcd     0xe350000a
    dcd     0x15940398
    dcd     0x13500000
    dcd     0x0a000002
    bl      func_ov107_020cb100
    dcd     0xe3a00000
    dcd     0xe5840398
    dcd     0xe1a00004
    bl      func_ov107_020c7ca4
    dcd     0xe8bd8010
}
