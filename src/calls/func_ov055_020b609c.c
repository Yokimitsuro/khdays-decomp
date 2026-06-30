extern void func_0202a634(void);
extern void func_ov055_020b63d0(void);
extern void data_ov055_020b7740(void);
extern void data_ov055_020b76c8(void);

asm void func_ov055_020b609c(void)
{
    dcd     0xe92d4010
    dcd     0xe59f0034
    dcd     0xe3a02000
    dcd     0xe5904000
    dcd     0xe59f102c
    dcd     0xe2840f65
    dcd     0xe2800b0b
    dcd     0xe5802014
    dcd     0xe5d43009
    dcd     0xe2800018
    dcd     0xe3a02001
    dcd     0xe2833007
    bl      func_0202a634
    dcd     0xe1a00004
    bl      func_ov055_020b63d0
    dcd     0xe8bd8010
    dcd     data_ov055_020b7740
    dcd     data_ov055_020b76c8
}
