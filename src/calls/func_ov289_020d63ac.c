extern char data_02041dc8[];
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov289_020d641c(void);

asm void func_ov289_020d63ac(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01001
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe5801394
    dcd     0xe594000c
    dcd     0xe2843010
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59f0028
    dcd     0xe284301c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a00000
    dcd     0xe5840008
    dcd     0xe5840058
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     data_02041dc8
    dcd     func_ov289_020d641c
}
