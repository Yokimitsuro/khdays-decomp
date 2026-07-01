extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov270_020d50a0(void);

asm void func_ov270_020d5054(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01004
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5c40050
    dcd     0xe5840030
    dcd     0xe5c40051
    dcd     0xe5c40053
    dcd     0xe5840054
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov270_020d50a0
}
