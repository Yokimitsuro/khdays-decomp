extern char data_ov083_020b9ad4[];
extern void func_0202a634(void);
extern void func_ov083_020b964c(void);

asm void func_ov083_020b9010(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840edf
    dcd     0xe2803a02
    dcd     0xe2840a02
    dcd     0xe3a01000
    dcd     0xe5c01df0
    dcd     0xe5831114
    dcd     0xe5d42009
    dcd     0xe59f1018
    dcd     0xe2830004
    dcd     0xe2823007
    dcd     0xe3a02001
    bl      func_0202a634
    dcd     0xe1a00004
    bl      func_ov083_020b964c
    dcd     0xe8bd8010
    dcd     data_ov083_020b9ad4
}
