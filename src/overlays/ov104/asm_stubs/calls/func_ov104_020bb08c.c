extern char data_ov104_020bc2a0[];
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0202a7dc(void);
extern void func_ov022_02091228(void);

asm void func_ov104_020bb08c(void)
{
    dcd     0xe92d4038
    dcd     0xe59f1030
    dcd     0xe1a05000
    dcd     0xe2850a02
    dcd     0xe5911000
    dcd     0xe5900644
    dcd     0xe28110fc
    dcd     0xe2814b0b
    bl      func_ov022_02091228
    dcd     0xe2850a02
    dcd     0xe5900644
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe2840004
    bl      func_0202a7dc
    dcd     0xe8bd8038
    dcd     data_ov104_020bc2a0
}
