extern void func_0202a7dc(void);
extern void func_ov022_02091228(void);
extern void data_ov075_020b9e20(void);

asm void func_ov075_020b87c4(void)
{
    dcd     0xe92d4010
    dcd     0xe59f1034
    dcd     0xe1a04000
    dcd     0xe5910000
    dcd     0xe2800f6b
    dcd     0xe2800b0b
    bl      func_0202a7dc
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800030
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800060
    bl      func_ov022_02091228
    dcd     0xe8bd8010
    dcd     data_ov075_020b9e20
}
