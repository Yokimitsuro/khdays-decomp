extern void func_0201e1d0(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void GX_SetBankForBG(void);
extern void GX_SetBankForOBJ(void);
extern void GX_SetBankForBGExtPltt(void);
extern void GX_SetBankForSubBG(void);
extern void GX_SetBankForSubOBJ(void);
extern void GX_SetBankForSubBGExtPltt(void);
extern void func_020056b4(void);
extern void GXS_SetGraphicsMode(void);

asm void func_ov011_0205d324(void)
{
    dcd     0xe92d4008
    bl      func_0201e1d0
    dcd     0xe3e0000f
    bl      func_0201e374
    dcd     0xe3e0000f
    bl      func_0201e3cc
    mov r0, #1
    bl      GX_SetBankForBG
    dcd     0xe3a00002
    bl      GX_SetBankForOBJ
    dcd     0xe3a00010
    bl      GX_SetBankForBGExtPltt
    dcd     0xe3a00004
    bl      GX_SetBankForSubBG
    dcd     0xe3a00008
    bl      GX_SetBankForSubOBJ
    dcd     0xe3a00080
    bl      GX_SetBankForSubBGExtPltt
    mov r0, #1
    dcd     0xe3a01000
    dcd     0xe1a02001
    bl      func_020056b4
    dcd     0xe59f1174
    dcd     0xe3a0c301
    dcd     0xe1d130b0
    dcd     0xe59f216c
    mov r0, #0
    dcd     0xe2033043
    dcd     0xe3833080
    dcd     0xe1c130b0
    dcd     0xe1d130b2
    dcd     0xe2033043
    dcd     0xe3833f41
    dcd     0xe1c130b2
    dcd     0xe1d130b4
    dcd     0xe2033043
    dcd     0xe3833e29
    dcd     0xe1c130b4
    dcd     0xe1d130b6
    dcd     0xe2033043
    dcd     0xe3833084
    dcd     0xe3833b01
    dcd     0xe1c130b6
    dcd     0xe59c3000
    dcd     0xe3c33c1f
    dcd     0xe3833c1f
    dcd     0xe58c3000
    dcd     0xe59c3000
    dcd     0xe0032002
    dcd     0xe3822010
    dcd     0xe3822602
    dcd     0xe58c2000
    dcd     0xe1d120b0
    dcd     0xe3c22003
    dcd     0xe3822003
    dcd     0xe1c120b0
    dcd     0xe1d120b2
    dcd     0xe3c22003
    dcd     0xe1c120b2
    dcd     0xe1d120b4
    dcd     0xe3c22003
    dcd     0xe3822001
    dcd     0xe1c120b4
    dcd     0xe1d120b6
    dcd     0xe3c22003
    dcd     0xe3822002
    dcd     0xe1c120b6
    bl      GXS_SetGraphicsMode
    dcd     0xe59f00c4
    dcd     0xe59f10bc
    dcd     0xe1d030b0
    dcd     0xe240c008
    dcd     0xe59f20b8
    dcd     0xe2033043
    dcd     0xe3833080
    dcd     0xe1c030b0
    dcd     0xe1d030b2
    dcd     0xe2033043
    dcd     0xe3833f41
    dcd     0xe1c030b2
    dcd     0xe1d030b4
    dcd     0xe2033043
    dcd     0xe3833e29
    dcd     0xe1c030b4
    dcd     0xe1d030b6
    dcd     0xe2033043
    dcd     0xe3833084
    dcd     0xe3833b01
    dcd     0xe1c030b6
    dcd     0xe59c3000
    dcd     0xe3c33c1f
    dcd     0xe3833c1f
    dcd     0xe58c3000
    dcd     0xe59c3000
    dcd     0xe0031001
    dcd     0xe3811010
    dcd     0xe3811602
    dcd     0xe58c1000
    dcd     0xe1d010b0
    dcd     0xe3c11003
    dcd     0xe3811003
    dcd     0xe1c010b0
    dcd     0xe1d010b2
    dcd     0xe3c11003
    dcd     0xe1c010b2
    dcd     0xe1d010b4
    dcd     0xe3c11003
    dcd     0xe3811001
    dcd     0xe1c010b4
    dcd     0xe1d010b6
    dcd     0xe3c11003
    dcd     0xe3811002
    dcd     0xe1c010b6
    dcd     0xe1d200b0
    dcd     0xe3800902
    dcd     0xe1c200b0
    dcd     0xe8bd8008
    dcd     0x04000008
    dcd     0xffcfffef
    dcd     0x04001008
    dcd     0x04000304
}
