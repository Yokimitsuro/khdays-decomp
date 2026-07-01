extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_0202aa9c(void);
extern void func_ov003_0204e4b8(void);
extern void func_ov003_0204e6b8(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204e5b0(void)
{
    dcd     0xe92d40f8
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a04000
    dcd     0xe2840a01
    dcd     0xe5900e10
    dcd     0xe3500000
    dcd     0x1a000002
    bl      func_ov105_020bd7c4
    dcd     0xe2841a01
    dcd     0xe5810e14
    dcd     0xe2840f42
    bl      func_0202aa9c
    dcd     0xe1d420b0
    dcd     0xe3a05000
    dcd     0xe3520000
    dcd     0xda000010
    dcd     0xe2846e21
    dcd     0xe2847e63
    dcd     0xe0840105
    dcd     0xe2800a01
    dcd     0xe5901750
    dcd     0xe1a00005
    bl      func_ov003_0204e4b8
    dcd     0xe1a00006
    bl      func_0202aa9c
    dcd     0xe1a00007
    bl      func_0202aa9c
    dcd     0xe1d420b0
    dcd     0xe2855001
    dcd     0xe2866f42
    dcd     0xe1550002
    dcd     0xe2877f42
    dcd     0xbafffff0
    dcd     0xe2841a01
    dcd     0xe5910774
    dcd     0xe3500010
    dcd     0xaa000008
    dcd     0xe2802001
    dcd     0xe2420010
    dcd     0xe5812774
    bl      func_0201e374
    dcd     0xe2840a01
    dcd     0xe5900774
    dcd     0xe2400010
    bl      func_0201e3cc
    dcd     0xea000010
    dcd     0xe3520000
    dcd     0xe3a03000
    dcd     0xda00000b
    dcd     0xe1a01003
    dcd     0xe2632000
    dcd     0xe0840103
    dcd     0xe1a02182
    dcd     0xe2800a01
    dcd     0xe580277c
    dcd     0xe580178c
    dcd     0xe580179c
    dcd     0xe1d400b0
    dcd     0xe2833001
    dcd     0xe1530000
    dcd     0xbafffff4
    dcd     0xe59f0008
    dcd     0xe8bd80f8
    mov r0, #0
    dcd     0xe8bd80f8
    dcd     func_ov003_0204e6b8
}
