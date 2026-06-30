extern void func_0203b9fc(void);
extern void func_0203c7ac(void);

asm void func_ov240_020ce2ac(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5d41311
    dcd     0xe2840c03
    dcd     0xe1d021d0
    dcd     0xe1a01f81
    dcd     0xe5940388
    dcd     0xe1a03fa1
    dcd     0xe3a01000
    bl      func_0203b9fc
    dcd     0xe5940388
    dcd     0xe3a01000
    bl      func_0203c7ac
    dcd     0xe8bd8010
}
