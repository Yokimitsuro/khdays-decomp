extern void NNSi_FndGetCurrentRootHeap(void);
extern void GFXi_EnqueueCommand(void);
extern void func_ov003_0204d6c8(void);
extern void func_ov003_0204e91c(void);
extern void func_ov003_0204ef68(void);
extern void func_ov003_0204f460(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204f33c(void)
{
    dcd     0xe92d4070
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
    dcd     0xe5900774
    dcd     0xe3500000
    dcd     0x1a00001e
    dcd     0xe1d420b0
    dcd     0xe3a06000
    dcd     0xe3520000
    dcd     0xda00000a
    dcd     0xe0840106
    dcd     0xe590102c
    dcd     0xe2420001
    dcd     0xe1510000
    dcd     0xaa000001
    dcd     0xe1a00006
    bl      func_ov003_0204d6c8
    dcd     0xe1d420b0
    dcd     0xe2866001
    dcd     0xe1560002
    dcd     0xbafffff4
    dcd     0xe2840fee
    dcd     0xe2802b05
    dcd     0xe3a00009
    dcd     0xe3a01000
    dcd     0xe3a03c06
    bl      GFXi_EnqueueCommand
    dcd     0xe2840fee
    dcd     0xe2802b05
    dcd     0xe3a00019
    dcd     0xe3a01000
    dcd     0xe3a03c06
    bl      GFXi_EnqueueCommand
    dcd     0xe2840a01
    dcd     0xe3a01010
    dcd     0xe5801e0c
    dcd     0xea00000d
    dcd     0xe2840fee
    dcd     0xe2802b05
    dcd     0xe3a00019
    dcd     0xe3a01000
    dcd     0xe3a03c06
    bl      GFXi_EnqueueCommand
    dcd     0xe2840a01
    dcd     0xe5901774
    dcd     0xe2611010
    dcd     0xe3510000
    dcd     0xe5801e0c
    dcd     0xd3a01000
    dcd     0xd59f5028
    dcd     0xd5801e0c
    dcd     0xe1a00004
    bl      func_ov003_0204ef68
    dcd     0xe2840a01
    dcd     0xe3550000
    dcd     0x05901774
    dcd     0x02811001
    dcd     0x13a01000
    dcd     0xe5801774
    dcd     0xe1a00005
    dcd     0xe8bd8070
    dcd     func_ov003_0204f460
}
