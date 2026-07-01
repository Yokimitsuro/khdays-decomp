extern char data_02041dc8[];
extern void func_ov022_02091540(void);
extern void func_ov022_02091b48(void);
extern void func_ov022_02091d80(void);

asm void func_ov068_020b6c64(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd018
    dcd     0xe1a05001
    dcd     0xe5951004
    dcd     0xe1a04002
    dcd     0xe0811004
    dcd     0xe28dc00c
    dcd     0xe5851004
    dcd     0xe28530cc
    dcd     0xe1a06000
    dcd     0xe8930007
    dcd     0xe88c0007
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe59f0070
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59d1004
    dcd     0xe1a0200c
    dcd     0xe2811a25
    dcd     0xe58d1004
    dcd     0xe1a00006
    dcd     0xe1a01005
    bl      func_ov022_02091b48
    dcd     0xe3a00002
    dcd     0xe5c50002
    dcd     0xe1a01004
    dcd     0xe2850028
    bl      func_ov022_02091540
    dcd     0xe3500000
    dcd     0x13a00003
    dcd     0x15c50002
    dcd     0xe1d500d2
    dcd     0xe3500003
    dcd     0x1a000004
    dcd     0xe3a02000
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe5852004
    bl      func_ov022_02091d80
    dcd     0xe3a00000
    dcd     0xe28dd018
    dcd     0xe8bd8070
    dcd     data_02041dc8
}
