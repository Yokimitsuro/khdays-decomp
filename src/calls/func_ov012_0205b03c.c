extern void NNSi_FndFreeFromDefaultHeap(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern void WM_EndKeySharing_0x0205bb78(void);
extern void data_ov012_0205c2a0(void);
extern void data_ov012_0205cb20(void);
extern void func_0201e4a8(void);
extern void func_02020aa8(void);
extern void func_0202f818(void);

asm void func_ov012_0205b03c(void)
{
    dcd     0xe92d4010
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a04000
    dcd     0xe2840902
    dcd     0xe5900bf8
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe2840902
    dcd     0xe5900bfc
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe2840fd3
    dcd     0xe2800b22
    bl      WM_EndKeySharing_0x0205bb78
    dcd     0xe2840d2d
    dcd     0xe2800902
    bl      func_0202f818
    dcd     0xe3a00003
    dcd     0xe3a01000
    bl      func_02020aa8
    dcd     0xe59f1030
    dcd     0xe3a00000
    bl      func_0201e4a8
    dcd     0xe59f0028
    dcd     0xe3e01000
    dcd     0xe5801000
    dcd     0xe59f0020
    dcd     0xe3a01000
    dcd     0xe5801000
    dcd     0xe59f1018
    dcd     0xe1d100b0
    dcd     0xe3800902
    dcd     0xe1c100b0
    dcd     0xe8bd8010
    dcd     0x00000018
    dcd     data_ov012_0205c2a0
    dcd     data_ov012_0205cb20
    dcd     0x04000304
}
