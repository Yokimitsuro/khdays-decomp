extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov134_020cde44(void);

asm void func_ov134_020cddf8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01007
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe3a00000
    dcd     0xe5840030
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov134_020cde44
}
