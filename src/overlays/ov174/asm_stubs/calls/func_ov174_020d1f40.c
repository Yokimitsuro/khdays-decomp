extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov174_020d1fac(void);

asm void func_ov174_020d1f40(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe584000c
    dcd     0xe3500000
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe3a02000
    dcd     0x1a000004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5840048
    dcd     0xe5c40084
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov174_020d1fac
}
