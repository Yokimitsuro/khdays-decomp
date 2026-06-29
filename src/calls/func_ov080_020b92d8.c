extern void func_02030788(void);
extern void func_ov022_020a35f4(void);

asm void func_ov080_020b92d8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe1a04001
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2850064
    dcd     0xe5952464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5852464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe285006c
    dcd     0xe595246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe585246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe3540000
    dcd     0xe1a00005
    dcd     0x0a000002
    dcd     0xe3a01022
    bl      func_ov022_020a35f4
    dcd     0xe8bd8038
    dcd     0xe3a01021
    bl      func_ov022_020a35f4
    dcd     0xe8bd8038
}
