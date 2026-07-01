extern void func_ov107_020c9ee8(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov140_020d145c(void);

asm void func_ov140_020d13c8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940000
    dcd     0xe5d0117a
    dcd     0xe1a01f81
    dcd     0xe1b01fa1
    dcd     0x1a000003
    dcd     0xe5d0117c
    dcd     0xe1a01f81
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe1d0c6b0
    dcd     0xe3a01003
    dcd     0xe3a02000
    dcd     0xe1a0380c
    dcd     0xe1a03c23
    dcd     0xe3833040
    dcd     0xe3ccccff
    dcd     0xe1a03c03
    dcd     0xe18c3823
    dcd     0xe1c036b0
    dcd     0xe5940000
    dcd     0xe5900390
    bl      func_ov107_020c9ee8
    dcd     0xe5940000
    dcd     0xe3a01008
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5c40055
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov140_020d145c
}
