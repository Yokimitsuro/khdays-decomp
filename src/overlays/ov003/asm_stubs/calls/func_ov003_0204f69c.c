extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_02020a78(void);
extern void func_ov003_0204e91c(void);
extern void func_ov003_0204ef68(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204f69c(void)
{
    dcd     0xe92d4010
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
    dcd     0xe2841a01
    dcd     0xe5910774
    dcd     0xe3500010
    dcd     0xaa000008
    dcd     0xe2802001
    dcd     0xe2620000
    dcd     0xe5812774
    bl      func_0201e374
    dcd     0xe2840a01
    dcd     0xe5900774
    dcd     0xe2600000
    bl      func_0201e3cc
    dcd     0xea000004
    dcd     0xe3a00006
    dcd     0xe3a01000
    bl      func_02020a78
    dcd     0xe3e00001
    dcd     0xe8bd8010
    dcd     0xe1a00004
    bl      func_ov003_0204ef68
    mov r0, #0
    dcd     0xe8bd8010
}
