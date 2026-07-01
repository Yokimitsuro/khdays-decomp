extern void func_02020400(void);
extern void func_02031258(void);
extern void func_ov002_020766e0(void);
extern void func_ov002_02077b30(void);

asm void func_ov021_0207fd98(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe1a04000
    dcd     0xe5d431b8
    dcd     0xe5940008
    dcd     0xe3530003
    dcd     0x8a00003f
    dcd     0xe5912014
    dcd     0xe3120020
    dcd     0x0a000027
    dcd     0xe3a02003
    dcd     0xe5cd2004
    dcd     0xe5dd3008
    dcd     0xe5d1200c
    dcd     0xe2841c01
    dcd     0xe3c330c0
    dcd     0xe1a02f02
    dcd     0xe1832c22
    dcd     0xe5cd2008
    dcd     0xe1d13bde
    dcd     0xe3a02006
    dcd     0xe5cd3009
    dcd     0xe1d13bde
    dcd     0xe0200293
    dcd     0xe1d007d8
    dcd     0xe3500000
    dcd     0x1a00000b
    dcd     0xe1d11bdb
    dcd     0xe2420007
    dcd     0xe1510000
    dcd     0x1a000001
    bl      func_ov002_02077b30
    dcd     0xe5c401bb
    dcd     0xe5dd1008
    dcd     0xe5d401bb
    dcd     0xe3c1103f
    dcd     0xe200003f
    dcd     0xe1810000
    dcd     0xe5cd0008
    dcd     0xe28d1004
    dcd     0xe1a00004
    dcd     0xe3a02006
    bl      func_ov002_020766e0
    dcd     0xe3500000
    dcd     0x0a000019
    dcd     0xe3a00004
    dcd     0xe5c401b8
    dcd     0xe28dd00c
    mov r0, #0
    dcd     0xe8bd8018
    dcd     0xe3530000
    dcd     0x1a000012
    mov r0, #1
    dcd     0xe5cd0000
    dcd     0xe5d40011
    dcd     0xe5cd0001
    dcd     0xe5941008
    dcd     0xe5910054
    dcd     0xe1d114be
    dcd     0xe0440000
    bl      func_02020400
    dcd     0xe1cd00b2
    dcd     0xe28d1000
    dcd     0xe3a00005
    dcd     0xe3a02004
    bl      func_02031258
    mov r0, #1
    dcd     0xe5c401b8
    dcd     0xe28dd00c
    mov r0, #0
    dcd     0xe8bd8018
    dcd     0xe3a00008
    dcd     0xe28dd00c
    dcd     0xe8bd8018
}
