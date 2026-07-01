extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov293_020d273c(void);

asm void func_ov293_020d26d8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01001
    dcd     0xe5940000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f202c
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe08030c3
    dcd     0xe5843014
    dcd     0xe3a00000
    dcd     0xe5840040
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x66666667
    dcd     func_ov293_020d273c
}
