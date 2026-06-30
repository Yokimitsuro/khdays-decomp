extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov298_020d46d0(void);

asm void func_ov298_020d467c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe3a00c09
    dcd     0xe5840050
    dcd     0xe3a00eff
    dcd     0xe5840038
    dcd     0xe3a00000
    dcd     0xe5840044
    dcd     0xe5c40097
    dcd     0xe5840078
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov298_020d46d0
}
