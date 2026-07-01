extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void data_ov270_020d6854(void);
extern void func_ov270_020d5b2c(void);

asm void func_ov270_020d5ac4(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01006
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe59f003c
    dcd     0xe28d1000
    dcd     0xe1d020b2
    dcd     0xe1d000b0
    dcd     0xe1cd20b2
    dcd     0xe1cd00b0
    dcd     0xe5940000
    dcd     0xe5903024
    dcd     0xe3530000
    dcd     0x0a000001
    dcd     0xe3a02004
    dcd     0xe12fff33
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     data_ov270_020d6854
    dcd     func_ov270_020d5b2c
}
