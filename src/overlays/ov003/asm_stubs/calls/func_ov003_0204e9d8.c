extern char data_ov003_0204f724[];
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a818(void);
extern void func_0202a928(void);
extern void func_0202accc(void);
extern void func_ov003_0204e91c(void);
extern void func_ov003_0204eb84(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204e9d8(void)
{
    dcd     0xe92d4ff8
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a05000
    dcd     0xe2850a01
    dcd     0xe5900e10
    dcd     0xe3a06000
    dcd     0xe3500000
    dcd     0x1a000002
    bl      func_ov105_020bd7c4
    dcd     0xe2851a01
    dcd     0xe5810e14
    dcd     0xe1a00005
    bl      func_ov003_0204e91c
    dcd     0xe5950054
    dcd     0xe3500001
    dcd     0x1a000056
    dcd     0xe1d500b0
    dcd     0xe3a0a000
    dcd     0xe3500000
    dcd     0xda000052
    dcd     0xe59fb14c
    dcd     0xe2857d5b
    dcd     0xe2858ea5
    dcd     0xe2859ee7
    dcd     0xe2854a01
    dcd     0xe085210a
    dcd     0xe2821a01
    dcd     0xe5910764
    dcd     0xe3500000
    dcd     0x1a000022
    dcd     0xe5910750
    dcd     0xe2803f4b
    dcd     0xe5813750
    dcd     0xe592202c
    dcd     0xe79b0102
    dcd     0xe1530000
    dcd     0xba00002f
    dcd     0xe3520000
    dcd     0x1a000005
    mov r0, #1
    dcd     0xe5810764
    mov r0, #0
    dcd     0xe5840774
    dcd     0xe59f60f4
    dcd     0xea000027
    dcd     0xe3520003
    dcd     0x0a000025
    mov r0, #1
    dcd     0xe5810764
    dcd     0xe1a00008
    dcd     0xe3a01000
    dcd     0xe1a02007
    dcd     0xe3a03004
    bl      func_0202accc
    dcd     0xe085010a
    dcd     0xe2800a01
    dcd     0xe5900290
    dcd     0xe3500000
    dcd     0x0a000019
    dcd     0xe1a00009
    dcd     0xe3a01000
    dcd     0xe28920e0
    dcd     0xe3a03004
    bl      func_0202accc
    dcd     0xea000013
    dcd     0xe1a00008
    dcd     0xe3a01a01
    bl      func_0202a928
    dcd     0xe3100001
    dcd     0x0a00000e
    dcd     0xe1a00008
    dcd     0xe3a01000
    dcd     0xe1a02007
    dcd     0xe3a03005
    bl      func_0202accc
    dcd     0xe085010a
    dcd     0xe2800a01
    dcd     0xe5900290
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe1a00009
    dcd     0xe3a01000
    dcd     0xe28920e0
    dcd     0xe3a03005
    bl      func_0202accc
    dcd     0xe1a00008
    dcd     0xe3a01a01
    bl      func_0202a818
    dcd     0xe085010a
    dcd     0xe2800a01
    dcd     0xe5900290
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe1a00009
    dcd     0xe3a01a01
    bl      func_0202a818
    dcd     0xe2877024
    dcd     0xe2888f42
    dcd     0xe2899f42
    dcd     0xe28aa001
    dcd     0xe1d500b0
    dcd     0xe15a0000
    dcd     0xbaffffb1
    dcd     0xe1a00006
    dcd     0xe8bd8ff8
    dcd     data_ov003_0204f724
    dcd     func_ov003_0204eb84
}
