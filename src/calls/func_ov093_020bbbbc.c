extern void func_01fff774(void);
extern void func_0202aee0(void);

asm void func_ov093_020bbbbc(void)
{
    dcd     0xe92d4038
    dcd     0xe59026bc
    dcd     0xe1a05001
    dcd     0xe352002f
    dcd     0x13520030
    dcd     0x1595111c
    dcd     0x13510000
    dcd     0x13a01000
    dcd     0x1585111c
    dcd     0xe595111c
    dcd     0xe3510002
    dcd     0x18bd8038
    dcd     0xe5900020
    dcd     0xe3a01000
    dcd     0xe2800004
    bl      func_0202aee0
    dcd     0xe1a04000
    dcd     0xe3540a01
    dcd     0xd8bd8038
    dcd     0xe2850e12
    dcd     0xe2442a01
    dcd     0xe3a01000
    bl      func_01fff774
    dcd     0xe2850e12
    dcd     0xe2442a01
    dcd     0xe3a01002
    bl      func_01fff774
    dcd     0xe2850e12
    dcd     0xe2442a01
    dcd     0xe3a01001
    bl      func_01fff774
    dcd     0xe8bd8038
}
