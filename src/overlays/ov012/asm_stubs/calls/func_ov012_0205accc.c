extern void data_ov012_0205cb20(void);
extern void func_020115b8(void);
extern void func_02032f5c(void);
extern void func_ov012_0205ac40(void);

asm void func_ov012_0205accc(void)
{
    dcd     0xe92d4010
    dcd     0xe59f0040
    dcd     0xe5904000
    dcd     0xe3540000
    dcd     0x08bd8010
    dcd     0xe2840902
    dcd     0xe5d00be1
    dcd     0xe3500000
    dcd     0x0a000005
    bl      func_020115b8
    dcd     0xe59f001c
    dcd     0xe3a01000
    dcd     0xe5900000
    dcd     0xe2800902
    dcd     0xe5c01be1
    dcd     0xe1a00004
    bl      func_ov012_0205ac40
    bl      func_02032f5c
    dcd     0xe8bd8010
    dcd     data_ov012_0205cb20
}
