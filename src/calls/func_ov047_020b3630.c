extern void func_ov022_02083f90(void);
extern void func_ov022_0209145c(void);
extern void func_ov022_02091474(void);
extern void func_ov022_020912d8(void);
extern void func_02030788(void);
extern void func_ov022_020ad588(void);

asm void func_ov047_020b3630(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_ov022_02083f90
    dcd     0xe2842a02
    dcd     0xe1a01000
    dcd     0xe5920644
    bl      func_ov022_0209145c
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_02091474
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_020912d8
    dcd     0xe3500000
    dcd     0x1a000013
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
    dcd     0x1a000006
    dcd     0xe284006c
    dcd     0xe594246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe584246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe1a00004
    bl      func_ov022_020ad588
    dcd     0xe8bd8010
}
