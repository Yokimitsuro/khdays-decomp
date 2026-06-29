extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0202a7dc(void);
extern void func_ov002_02051fc8(void);
extern void func_ov022_02091228(void);

asm void func_ov083_020b9058(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe2840f4e
    dcd     0xe2800b0b
    dcd     0xe2841e91
    bl      func_ov002_02051fc8
    dcd     0xe2840f63
    dcd     0xe2800b0b
    dcd     0xe2841e91
    bl      func_ov002_02051fc8
    dcd     0xe2840f7d
    dcd     0xe2800b0b
    bl      func_0202a7dc
    dcd     0xe8bd8010
}
