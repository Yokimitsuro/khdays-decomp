extern void func_ov002_02077b30(void);
extern void func_ov002_020766e0(void);
extern void func_ov017_0208079c(void);

asm void func_ov017_02080720(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd008
    dcd     0xe1a04000
    dcd     0xe5d401b4
    dcd     0xe3500000
    dcd     0x1a00000a
    dcd     0xe3a00001
    dcd     0xe5cd0000
    bl      func_ov002_02077b30
    dcd     0xe5cd0004
    dcd     0xe28d1000
    dcd     0xe1a00004
    dcd     0xe3a02006
    bl      func_ov002_020766e0
    dcd     0xe3a00002
    dcd     0xe5c401b4
    dcd     0xea000009
    dcd     0xe2840c01
    dcd     0xe1d01bd9
    dcd     0xe3e00000
    dcd     0xe1510000
    dcd     0x0a000004
    dcd     0xe3a00003
    dcd     0xe5c401b4
    dcd     0xe28dd008
    dcd     0xe59f000c
    dcd     0xe8bd8010
    dcd     0xe3a00000
    dcd     0xe28dd008
    dcd     0xe8bd8010
    dcd     func_ov017_0208079c
}
