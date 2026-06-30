extern void func_ov297_020d4168(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov297_020d4964(void);

asm void func_ov297_020d48fc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    bl      func_ov297_020d4168
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe3a00c09
    dcd     0xe5840050
    dcd     0xe3a00000
    dcd     0xe5840088
    dcd     0xe5942030
    dcd     0xe5941028
    dcd     0xe59f0020
    dcd     0xe0821001
    dcd     0xe5841030
    dcd     0xe5841034
    dcd     0xe5840054
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00001fe0
    dcd     func_ov297_020d4964
}
