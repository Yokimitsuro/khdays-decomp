extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov107_020c9ee8(void);
extern void func_ov145_020cf37c(void);
extern void func_ov145_020cf3d4(void);

asm void func_ov145_020cf300(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940000
    dcd     0xe2801c01
    dcd     0xe1d11cd6
    dcd     0xe3510004
    dcd     0x1a000007
    dcd     0xe3a01006
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f203c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0xe3a01001
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe5900394
    dcd     0xe3a02001
    bl      func_ov107_020c9ee8
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov145_020cf37c
    dcd     func_ov145_020cf3d4
}
