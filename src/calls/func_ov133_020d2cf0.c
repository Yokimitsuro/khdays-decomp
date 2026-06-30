extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov133_020d2d50(void);

asm void func_ov133_020d2cf0(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5941000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f103c
    dcd     0xe0030092
    dcd     0xe0c20391
    dcd     0xe0832002
    dcd     0xe1a00fa3
    dcd     0xe5941004
    dcd     0xe0802242
    dcd     0xe5812014
    dcd     0xe5910000
    dcd     0xe3a01008
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f200c
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     0x88888889
    dcd     func_ov133_020d2d50
}
