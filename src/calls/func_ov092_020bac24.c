extern void func_ov092_020bbf7c(void);
extern void func_ov092_020baed4(void);
extern void func_ov092_020baf30(void);
extern void func_ov022_020912d8(void);
extern void func_02030788(void);
extern void data_ov092_020bc4e0(void);

asm void func_ov092_020bac24(void)
{
    dcd     0xe92d4038
    dcd     0xe59f10b0
    dcd     0xe1a04000
    dcd     0xe5911000
    dcd     0xe2815f65
    bl      func_ov092_020bbf7c
    dcd     0xe2840c2a
    dcd     0xe1d02bfa
    dcd     0xe1a00004
    dcd     0xe2851b0b
    bl      func_ov092_020baed4
    dcd     0xe1a00004
    dcd     0xe2851b0b
    bl      func_ov092_020baf30
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800030
    bl      func_ov022_020912d8
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe2800060
    bl      func_ov022_020912d8
    dcd     0xe3500000
    dcd     0x18bd8038
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2840064
    dcd     0xe5942464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5842464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe284006c
    dcd     0xe594246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe584246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe8bd8038
    dcd     data_ov092_020bc4e0
}
