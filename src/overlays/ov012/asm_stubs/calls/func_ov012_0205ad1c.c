extern void GX_SetBankForBG(void);
extern void GX_SetBankForBGExtPltt(void);
extern void func_020056b4(void);
extern void func_0201e1d0(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_ov024_0208462c(void);

asm void func_ov012_0205ad1c(void)
{
    dcd     0xe92d4008
    dcd     0xe3e0000f
    bl      func_0201e374
    dcd     0xe3e0000f
    bl      func_0201e3cc
    bl      func_0201e1d0
    dcd     0xe3a00000
    dcd     0xe3a01001
    bl      func_ov024_0208462c
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe3a00001
    bl      func_020056b4
    dcd     0xe3a00003
    bl      GX_SetBankForBG
    dcd     0xe3a00000
    bl      GX_SetBankForBGExtPltt
    dcd     0xe59f007c
    dcd     0xe3a03301
    dcd     0xe1d020b0
    dcd     0xe2831fc1
    dcd     0xe2022043
    dcd     0xe3822084
    dcd     0xe1c020b0
    dcd     0xe1d020b2
    dcd     0xe2022043
    dcd     0xe3822e29
    dcd     0xe1c020b2
    dcd     0xe1d020b4
    dcd     0xe2022043
    dcd     0xe3822e4a
    dcd     0xe1c020b4
    dcd     0xe5932000
    dcd     0xe3c22c1f
    dcd     0xe5832000
    dcd     0xe1d020b0
    dcd     0xe3c22003
    dcd     0xe3822002
    dcd     0xe1c020b0
    dcd     0xe1d020b2
    dcd     0xe3c22003
    dcd     0xe3822001
    dcd     0xe1c020b2
    dcd     0xe1d020b4
    dcd     0xe3c22003
    dcd     0xe1c020b4
    dcd     0xe1d100b0
    dcd     0xe3c00902
    dcd     0xe1c100b0
    dcd     0xe8bd8008
    dcd     0x04000008
}
