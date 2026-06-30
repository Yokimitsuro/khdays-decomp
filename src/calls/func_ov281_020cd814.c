extern void func_ov107_020c9264(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov281_020cd870(void);

asm void func_ov281_020cd814(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01004
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe594300c
    dcd     0xe59f1028
    dcd     0xe3a02007
    bl      func_ov107_020c5af8
    dcd     0xe3a00000
    dcd     0xe5840018
    dcd     0xe5c4003c
    dcd     0xe5c4003d
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00000169
    dcd     func_ov281_020cd870
}
