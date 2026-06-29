extern void FX_Inv(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);

asm void func_ov299_020d410c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a04000
    dcd     0xe5842008
    dcd     0xe1a00001
    dcd     0xe5941004
    dcd     0xe28d2000
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe1a05000
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840028
    dcd     0xe1a00005
    dcd     0xe3a01932
    bl      FX_Inv
    dcd     0xe3500a01
    dcd     0xc3a00a01
    dcd     0xca000001
    dcd     0xe3500000
    dcd     0xb3a00000
    dcd     0xe1a01fc0
    dcd     0xe1a02681
    dcd     0xe3a01b02
    dcd     0xe0911680
    dcd     0xe18229a0
    dcd     0xe2a20000
    dcd     0xe1a01621
    dcd     0xe1811a00
    dcd     0xe2810b06
    dcd     0xe584002c
    dcd     0xe5942000
    dcd     0xe1d216b0
    dcd     0xe1a00801
    dcd     0xe1a00c20
    dcd     0xe3800001
    dcd     0xe3c11cff
    dcd     0xe1a00c00
    dcd     0xe1810820
    dcd     0xe1c206b0
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
