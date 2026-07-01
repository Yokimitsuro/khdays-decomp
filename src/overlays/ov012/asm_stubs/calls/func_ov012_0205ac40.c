extern void GXx_SetMasterBrightness_(void);
extern void func_ov024_02084e68(void);

asm void func_ov012_0205ac40(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850902
    dcd     0xe5901be8
    dcd     0xe3510000
    dcd     0xaa000006
    bl      func_ov024_02084e68
    dcd     0xe3500000
    dcd     0xd8bd8038
    dcd     0xe59f0058
    dcd     0xe3a01000
    bl      GXx_SetMasterBrightness_
    dcd     0xe8bd8038
    dcd     0xe3510010
    dcd     0xa8bd8038
    dcd     0xe2811001
    dcd     0xe5801be8
    dcd     0xe5901be4
    dcd     0xe3510000
    dcd     0x05900be8
    dcd     0x02604000
    dcd     0x15904be8
    dcd     0xe59f0024
    dcd     0xe1a01004
    bl      GXx_SetMasterBrightness_
    dcd     0xe2850902
    dcd     0xe5900bf4
    dcd     0xe1540000
    dcd     0xa1a04000
    dcd     0xe59f000c
    dcd     0xe1a01004
    bl      GXx_SetMasterBrightness_
    dcd     0xe8bd8038
    dcd     0x0400106c
    dcd     0x0400006c
}
