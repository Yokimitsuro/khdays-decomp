extern void NNSi_FndGetCurrentRootHeap(void);
extern void G2S_GetBG0ScrPtr(void);
extern void G2_GetBG3ScrPtr(void);
extern void func_02013484(void);
extern void func_02033b24(void);
extern void func_ov003_0204cac0(void);
extern void func_ov003_0204e91c(void);
extern void func_ov003_0204ef68(void);
extern void func_ov003_0204f5cc(void);
extern void func_ov003_0204f69c(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204f460(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd018
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a04000
    dcd     0xe2840a01
    dcd     0xe5900e10
    dcd     0xe3500000
    dcd     0x1a000002
    bl      func_ov105_020bd7c4
    dcd     0xe2841a01
    dcd     0xe5810e14
    dcd     0xe1a00004
    bl      func_ov003_0204e91c
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe2811001
    dcd     0xe5801774
    dcd     0xe3510002
    dcd     0x1a000023
    bl      G2_GetBG3ScrPtr
    dcd     0xe3a01008
    dcd     0xe58d1000
    dcd     0xe3a01016
    dcd     0xe58d1004
    dcd     0xe3a01020
    dcd     0xe3a02000
    dcd     0xe58d1008
    dcd     0xe3a01018
    dcd     0xe58d100c
    dcd     0xe3a01010
    dcd     0xe58d1010
    dcd     0xe3a01002
    dcd     0xe58d1014
    dcd     0xe2841a01
    dcd     0xe5911de4
    dcd     0xe1a03002
    bl      func_02013484
    bl      G2S_GetBG0ScrPtr
    dcd     0xe3a01008
    dcd     0xe3a02000
    dcd     0xe58d1000
    dcd     0xe3a01016
    dcd     0xe58d1004
    dcd     0xe3a01020
    dcd     0xe58d1008
    dcd     0xe3a01018
    dcd     0xe58d100c
    dcd     0xe3a01010
    dcd     0xe58d1010
    dcd     0xe3a01002
    dcd     0xe58d1014
    dcd     0xe2841a01
    dcd     0xe5911de4
    dcd     0xe1a03002
    bl      func_02013484
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe3510040
    dcd     0xa3a01000
    dcd     0xa5801774
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe3510010
    dcd     0xb5801e08
    dcd     0xba000004
    dcd     0xe3510030
    dcd     0xb3a0100f
    dcd     0xb5801e08
    dcd     0xa261103f
    dcd     0xa5801e08
    dcd     0xe1a00004
    bl      func_ov003_0204ef68
    bl      func_ov003_0204cac0
    dcd     0xe3500000
    dcd     0x028dd018
    dcd     0xe3a00000
    dcd     0x08bd8010
    dcd     0xe3a01001
    bl      func_02033b24
    dcd     0xe2840a01
    dcd     0xe3a01000
    dcd     0xe5801774
    dcd     0xe5801e08
    dcd     0xe5900778
    dcd     0xe3500000
    dcd     0x059f0008
    dcd     0x159f0008
    dcd     0xe28dd018
    dcd     0xe8bd8010
    dcd     func_ov003_0204f5cc
    dcd     func_ov003_0204f69c
}
