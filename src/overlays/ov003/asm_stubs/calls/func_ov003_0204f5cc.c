extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov003_0204e91c(void);
extern void func_ov003_0204ef68(void);
extern void func_ov003_0204f08c(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204f5cc(void)
{
    dcd     0xe92d4038
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a04000
    dcd     0xe2840a01
    dcd     0xe5900e10
    dcd     0xe3a05000
    dcd     0xe3500000
    dcd     0x1a000002
    bl      func_ov105_020bd7c4
    dcd     0xe2841a01
    dcd     0xe5810e14
    dcd     0xe1a00004
    bl      func_ov003_0204e91c
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe3510000
    dcd     0x1a000004
    dcd     0xe3a01000
    dcd     0xe58017b0
    dcd     0xe3a0101f
    dcd     0xe58017b4
    dcd     0xea000012
    dcd     0xe59027b0
    dcd     0xe3e010be
    dcd     0xe2422006
    dcd     0xe58027b0
    dcd     0xe1520001
    dcd     0xaa000006
    dcd     0xe3a02001
    dcd     0xe58027ac
    dcd     0xe58017b0
    dcd     0xe3a01000
    dcd     0xe5801774
    dcd     0xe59f5040
    dcd     0xe5802778
    dcd     0xe2840a01
    dcd     0xe59017b4
    dcd     0xe2511001
    dcd     0xe58017b4
    dcd     0x43a01000
    dcd     0x458017b4
    dcd     0xe1a00004
    bl      func_ov003_0204ef68
    dcd     0xe3550000
    dcd     0x1a000003
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe2811001
    dcd     0xe5801774
    dcd     0xe1a00005
    dcd     0xe8bd8038
    dcd     func_ov003_0204f08c
}
