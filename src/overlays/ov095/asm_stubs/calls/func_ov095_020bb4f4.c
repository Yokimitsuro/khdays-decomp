extern void func_ov022_020923dc(void);
extern void func_01fff774(void);

asm void func_ov095_020bb4f4(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe2860f92
    dcd     0xe1a05001
    dcd     0xe2800b09
    dcd     0xe3a01005
    dcd     0xe1a04002
    bl      func_ov022_020923dc
    dcd     0xe3500000
    dcd     0x03a00000
    dcd     0x05c50001
    dcd     0xe59606bc
    dcd     0xe350002f
    dcd     0x13500032
    dcd     0x13a00000
    dcd     0x15c50001
    dcd     0xe1d500d1
    dcd     0xe3500001
    dcd     0x0a000002
    dcd     0xe3500002
    dcd     0x0a000005
    dcd     0xe8bd8070
    dcd     0xe59607b0
    dcd     0xe3500a09
    dcd     0xa3a00002
    dcd     0xa5c50001
    dcd     0xe8bd8070
    dcd     0xe59617b0
    dcd     0xe2850004
    dcd     0xe2411a09
    dcd     0xe0812004
    dcd     0xe3a01002
    bl      func_01fff774
    dcd     0xe8bd8070
}
