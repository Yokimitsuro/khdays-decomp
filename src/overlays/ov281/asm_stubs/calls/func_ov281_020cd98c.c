extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_0203c634(void);
extern void func_ov281_020cda08(void);

asm void func_ov281_020cd98c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01005
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe59003c0
    dcd     0xe1a02001
    bl      func_ov107_020c9ee8
    dcd     0xe594e000
    dcd     0xe3a01000
    dcd     0xe1de36b0
    dcd     0xe59f2034
    dcd     0xe1a00005
    dcd     0xe3c3ccff
    dcd     0xe1a03803
    dcd     0xe1a03c23
    dcd     0xe3833040
    dcd     0xe1a03c03
    dcd     0xe18c3823
    dcd     0xe1ce36b0
    dcd     0xe5841018
    dcd     0xe5c4103c
    dcd     0xe5c4103d
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov281_020cda08
}
