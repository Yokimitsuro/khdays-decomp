extern void NNSi_FndDestroyDoubleList(void);
extern void func_0203c7e8(void);
extern void func_0203d194(void);
extern void func_ov107_020c68ec(void);
extern void func_ov107_020c9eac(void);

asm void func_ov130_020cc1d0(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5940384
    bl      func_0203c7e8
    dcd     0xe5940390
    bl      func_ov107_020c9eac
    dcd     0xe5940394
    dcd     0xe5900000
    bl      func_0203c7e8
    dcd     0xe5940394
    bl      func_0203d194
    dcd     0xe2840fe6
    bl      NNSi_FndDestroyDoubleList
    dcd     0xe1a00004
    bl      func_ov107_020c68ec
    dcd     0xe8bd8010
}
