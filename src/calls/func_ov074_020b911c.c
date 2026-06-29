extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_ov022_02091228(void);

asm void func_ov074_020b911c(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800030
    bl      func_ov022_02091228
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe8bd8010
}
