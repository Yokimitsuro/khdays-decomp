extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov194_020ccf2c(void);

asm void func_ov194_020ccecc(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe590202c
    dcd     0xe3a0001e
    dcd     0xe00c0092
    dcd     0xe59f3034
    dcd     0xe1a00fac
    dcd     0xe0ce2c93
    dcd     0xe08ce00e
    dcd     0xe5942004
    dcd     0xe080e1ce
    dcd     0xe582e014
    dcd     0xe5920000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f200c
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     0x88888889
    dcd     func_ov194_020ccf2c
}
