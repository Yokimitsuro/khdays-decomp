extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov284_020ccbfc(void);

asm void func_ov284_020ccba0(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe3a01000
    dcd     0xe5950000
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe5950000
    dcd     0xe59f2030
    dcd     0xe590c3a8
    dcd     0xe1a00004
    dcd     0xe59c3008
    dcd     0xe1a01c03
    dcd     0xe1a01c21
    dcd     0xe3811001
    dcd     0xe3c330ff
    dcd     0xe20110ff
    dcd     0xe1831001
    dcd     0xe58c1008
    dcd     0xe1d412d0
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov284_020ccbfc
}
