extern void NNSi_FndFreeFromDefaultHeap(void);
extern char data_ov046_020b4b40[];
extern void func_0202a7dc(void);
extern void func_ov022_02091228(void);

asm void func_ov046_020b3a14(void)
{
    dcd     0xe92d4070
    dcd     0xe59f104c
    dcd     0xe1a06000
    dcd     0xe5910000
    dcd     0xe2804db2
    dcd     0xe2840004
    bl      func_0202a7dc
    dcd     0xe2845f4b
    dcd     0xe3a04000
    dcd     0xe1a00005
    bl      func_0202a7dc
    dcd     0xe2844001
    dcd     0xe3540006
    dcd     0xe2855e12
    dcd     0xbafffff9
    dcd     0xe2860a02
    dcd     0xe5900644
    bl      func_ov022_02091228
    dcd     0xe2860a02
    dcd     0xe5900644
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe8bd8070
    dcd     data_ov046_020b4b40
}
