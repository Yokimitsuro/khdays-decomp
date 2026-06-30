extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_0203c634(void);
extern void func_ov195_020d2574(void);

asm void func_ov195_020d2508(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5941000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f1048
    dcd     0xe0030092
    dcd     0xe0c20391
    dcd     0xe5945004
    dcd     0xe0822fa3
    dcd     0xe5852014
    dcd     0xe5950000
    dcd     0xe3a0100e
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5950000
    dcd     0xe3a01006
    dcd     0xe59003d0
    dcd     0xe3a02000
    bl      func_ov107_020c9ee8
    dcd     0xe1d412d0
    dcd     0xe59f200c
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x55555556
    dcd     func_ov195_020d2574
}
