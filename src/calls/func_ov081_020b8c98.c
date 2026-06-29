extern char data_ov081_020b96e0[];
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0202a7dc(void);
extern void func_ov022_02091228(void);

asm void func_ov081_020b8c98(void)
{
    dcd     0xe92d4038
    dcd     0xe59f1058
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5911000
    dcd     0xe5900644
    dcd     0xe281102c
    dcd     0xe2815b0b
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800030
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe2855018
    dcd     0xe3a04000
    dcd     0xe1a00005
    bl      func_0202a7dc
    dcd     0xe2844001
    dcd     0xe3540007
    dcd     0xe2855f43
    dcd     0xbafffff9
    dcd     0xe8bd8038
    dcd     data_ov081_020b96e0
}
