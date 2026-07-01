extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_02023eb4(void);
extern void func_ov293_020d28b4(void);

asm void func_ov293_020d2828(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840004
    dcd     0xe3500000
    dcd     0xe3a01002
    dcd     0x1a000008
    dcd     0xe3a00a02
    dcd     0xe5840018
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    mov r0, #0
    dcd     0xe5840040
    dcd     0xe5940000
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe59f001c
    bl      func_02023eb4
    dcd     0xe2800a01
    dcd     0xe5840044
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00005001
    dcd     func_ov293_020d28b4
}
